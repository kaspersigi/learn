#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>

// 在其他 include 之后
#define CREATE_TRACE_POINTS
#include <trace/events/mychar.h>

// 内核缓冲区
static char hello_buffer[512] = { 0 };

// 动态分配主设备号
const static unsigned CHARDEV_NUM = 6;
const static char* CHARDEV_NAME = "hello_world";

// 设备结构体
struct dev {
    dev_t devno; // 设备号
    int major; // 主设备号
    int minor; // 次设备号
    struct cdev* cdev; // cdev
    struct class* class; // 类
    struct device* device; // 设备
};

static struct dev mydev = {
    .devno = 0,
    .major = 0,
    .minor = 0,
    .cdev = NULL,
    .class = NULL,
    .device = NULL,
};

static int hello_open(struct inode* inode, struct file* fp)
{
    printk(KERN_INFO "char module: hello_world open success!\n");
    return 0;
}

static int hello_release(struct inode* inode, struct file* fp)
{
    printk(KERN_INFO "char module: hello_world release success!\n");
    return 0;
}

static ssize_t hello_read(struct file* fp, char __user* buf, size_t size, loff_t* pos)
{
    unsigned long p = *pos;
    unsigned int count = size;

    trace_char_slice('B', "hello_read");
    if (p >= 512)
        return 0; // ✅ 修改1: 返回 0 表示 EOF
    if (count > 512 - p) // ✅ 修改2: 修复边界计算
        count = 512 - p;
    if (copy_to_user(buf, hello_buffer + p, count) != 0) {
        printk(KERN_ERR "read error!\n");
        trace_char_slice('E', "");
        return -1;
    }
    *pos += count; // ✅ 修改3: 更新文件偏移
    trace_char_slice('E', "");

    return count;
}

static ssize_t hello_write(struct file* fp, const char __user* buf, size_t size, loff_t* pos)
{
    unsigned long p = *pos;
    unsigned int count = size;

    trace_char_slice('B', "hello_write");
    if (p >= 512)
        return -1;
    if (count > 512 - p) // ✅ 修改4: 修复边界计算
        count = 512 - p;
    if (copy_from_user(hello_buffer + p, buf + p, count) != 0) { // ✅ 修改5: hello_buffer + p
        printk(KERN_ERR "write error!\n");
        trace_char_slice('E', "");
        return -1;
    }
    *pos += count; // ✅ 修改6: 更新偏移（保持一致性）
    trace_char_slice('E', "");

    return count;
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .release = hello_release,
    .read = hello_read,
    .write = hello_write,
};

static int __init hello_init(void)
{
    int ret = alloc_chrdev_region(&mydev.devno, mydev.minor, CHARDEV_NUM, CHARDEV_NAME);

    if (ret < 0) {
        printk(KERN_ERR "Register char module: %s failed!\n", CHARDEV_NAME);
        return ret;
    } else {
        mydev.major = MAJOR(mydev.devno);
        printk(KERN_INFO "Register char module: %s success! major: %d, minor: %d\n", CHARDEV_NAME, mydev.major, mydev.minor);
    }
    mydev.cdev = cdev_alloc();
    cdev_init(mydev.cdev, &hello_fops);
    cdev_add(mydev.cdev, mydev.devno, CHARDEV_NUM);
    mydev.class = class_create(CHARDEV_NAME); // 👈 保持原样，不修改
    for (size_t i = mydev.minor; i < mydev.minor + CHARDEV_NUM; ++i) {
        mydev.device = device_create(mydev.class, NULL, MKDEV(mydev.major, i), NULL, "%s%zu", CHARDEV_NAME, i);
    }
    return 0;
}

static void __exit hello_exit(void)
{
    for (size_t i = mydev.minor; i < mydev.minor + CHARDEV_NUM; ++i) {
        device_destroy(mydev.class, MKDEV(mydev.major, i));
    }
    class_destroy(mydev.class);
    cdev_del(mydev.cdev);
    unregister_chrdev_region(mydev.devno, CHARDEV_NUM);
    printk(KERN_INFO "Unregister char module: hello_world success!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhuangzhuang Li <kaspersigi@outlook.com>");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("05.trace");