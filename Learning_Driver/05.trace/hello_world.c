#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/version.h>      // 用于内核版本判断

// 启用 trace event 定义（必须在 include trace 头文件前定义）
#define CREATE_TRACE_POINTS
#include <trace/events/mychar.h>

// 全局内核缓冲区，大小为 512 字节，初始化为 0
static char hello_buffer[512] = { 0 };

// 设备数量（次设备号范围）
#define CHARDEV_NUM     6
// 设备类和设备节点基础名称
#define CHARDEV_NAME    "hello_world"

// 设备管理结构体，用于统一管理设备号、cdev、class、device 等资源
struct dev {
    dev_t devno;                // 完整设备号（主+次）
    int major;                  // 主设备号
    int minor;                  // 起始次设备号
    struct cdev *cdev;          // 字符设备结构
    struct class *class;        // 设备类（用于 sysfs 和 udev）
    struct device *device;      // 设备实例（用于 /dev 节点）
};

// 全局设备实例
static struct dev mydev = {
    .devno = 0,
    .major = 0,
    .minor = 0,
    .cdev = NULL,
    .class = NULL,
    .device = NULL,
};

// 设备打开回调函数
static int hello_open(struct inode *inode, struct file *fp)
{
    printk(KERN_INFO "char module: %s open success!\n", CHARDEV_NAME);
    return 0;
}

// 设备关闭回调函数
static int hello_release(struct inode *inode, struct file *fp)
{
    printk(KERN_INFO "char module: %s release success!\n", CHARDEV_NAME);
    return 0;
}

// 设备读取回调函数
static ssize_t hello_read(struct file *fp, char __user *buf, size_t size, loff_t *pos)
{
    unsigned long p = *pos;          // 当前文件偏移
    unsigned int count = size;       // 用户请求读取的字节数

    // 记录函数入口（Begin）
    trace_char_slice('B', "hello_read");

    // 情况1：已读到缓冲区末尾（EOF）
    if (p >= sizeof(hello_buffer)) {
        trace_char_slice('E', "EOF");   // 明确标记 EOF 退出
        return 0;
    }

    // 限制读取长度，防止越界
    if (count > sizeof(hello_buffer) - p)
        count = sizeof(hello_buffer) - p;

    // 将内核缓冲区数据拷贝到用户空间
    if (copy_to_user(buf, hello_buffer + p, count) != 0) {
        printk(KERN_ERR "read error: copy_to_user failed!\n");
        trace_char_slice('E', "error"); // 标记错误退出
        return -EFAULT;
    }

    // 更新文件偏移
    *pos += count;

    // 记录正常退出（End）
    trace_char_slice('E', "success");
    return count;
}

// 设备写入回调函数
static ssize_t hello_write(struct file *fp, const char __user *buf, size_t size, loff_t *pos)
{
    unsigned long p = *pos;          // 当前文件偏移
    unsigned int count = size;       // 用户请求写入的字节数

    // 记录函数入口（Begin）
    trace_char_slice('B', "hello_write");

    // 情况1：缓冲区已满，无法继续写入
    if (p >= sizeof(hello_buffer)) {
        trace_char_slice('E', "full");  // 明确标记“缓冲区满”退出
        return -ENOSPC;
    }

    // 限制写入长度，防止越界
    if (count > sizeof(hello_buffer) - p)
        count = sizeof(hello_buffer) - p;

    // 从用户空间拷贝数据到内核缓冲区
    // 注意：buf 是用户缓冲区起始地址，不应加偏移；偏移由 hello_buffer + p 处理
    if (copy_from_user(hello_buffer + p, buf, count) != 0) {
        printk(KERN_ERR "write error: copy_from_user failed!\n");
        trace_char_slice('E', "error"); // 标记错误退出
        return -EFAULT;
    }

    // 更新文件偏移
    *pos += count;

    // 记录正常退出（End）
    trace_char_slice('E', "success");
    return count;
}

// 文件操作函数集
static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .release = hello_release,
    .read = hello_read,
    .write = hello_write,
};

// 模块初始化函数
static int __init hello_init(void)
{
    int ret;

    // 动态分配主设备号和 CHARDEV_NUM 个次设备号
    ret = alloc_chrdev_region(&mydev.devno, 0, CHARDEV_NUM, CHARDEV_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate char device region for %s\n", CHARDEV_NAME);
        return ret;
    }

    // 提取主/次设备号
    mydev.major = MAJOR(mydev.devno);
    mydev.minor = MINOR(mydev.devno);
    printk(KERN_INFO "Registered %s: major=%d, minor=%d\n", CHARDEV_NAME, mydev.major, mydev.minor);

    // 分配并初始化 cdev 结构
    mydev.cdev = cdev_alloc();
    if (!mydev.cdev) {
        unregister_chrdev_region(mydev.devno, CHARDEV_NUM);
        return -ENOMEM;
    }
    cdev_init(mydev.cdev, &hello_fops);
    ret = cdev_add(mydev.cdev, mydev.devno, CHARDEV_NUM);
    if (ret < 0) {
        kfree(mydev.cdev);
        unregister_chrdev_region(mydev.devno, CHARDEV_NUM);
        return ret;
    }

    // 创建设备类：兼容 6.1（需 THIS_MODULE）和 6.6+（无需）
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    mydev.class = class_create(CHARDEV_NAME);
#else
    mydev.class = class_create(THIS_MODULE, CHARDEV_NAME);
#endif

    if (IS_ERR(mydev.class)) {
        ret = PTR_ERR(mydev.class);
        cdev_del(mydev.cdev);
        unregister_chrdev_region(mydev.devno, CHARDEV_NUM);
        return ret;
    }

    // 创建 CHARDEV_NUM 个设备节点（/dev/hello_world0, hello_world1, ...）
    for (unsigned int i = 0; i < CHARDEV_NUM; ++i) {
        dev_t devno = MKDEV(mydev.major, mydev.minor + i);
        struct device *dev = device_create(mydev.class, NULL, devno, NULL, "%s%u", CHARDEV_NAME, i);
        if (IS_ERR(dev)) {
            printk(KERN_ERR "Failed to create %s%u\n", CHARDEV_NAME, i);
            // 简化处理：不回滚已创建设备（实际项目中建议清理）
        }
    }

    return 0;
}

// 模块卸载函数
static void __exit hello_exit(void)
{
    // 销毁所有设备节点
    for (unsigned int i = 0; i < CHARDEV_NUM; ++i) {
        dev_t devno = MKDEV(mydev.major, mydev.minor + i);
        device_destroy(mydev.class, devno);
    }

    // 销毁设备类
    class_destroy(mydev.class);

    // 注销 cdev
    cdev_del(mydev.cdev);

    // 释放设备号
    unregister_chrdev_region(mydev.devno, CHARDEV_NUM);

    printk(KERN_INFO "Unregistered char module: %s\n", CHARDEV_NAME);
}

// 模块入口/出口声明
module_init(hello_init);
module_exit(hello_exit);

// 模块元信息
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhuangzhuang Li <kaspersigi@outlook.com>");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("05.trace");