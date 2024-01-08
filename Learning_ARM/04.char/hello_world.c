#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

static char hello_buffer[512] = { 0 };

static int hello_open(struct inode* inode, struct file* fp)
{
    return 0;
}

static int hello_release(struct inode* inode, struct file* fp)
{
    return 0;
}

static ssize_t hello_read(struct file* fp, char __user* buf, size_t size, loff_t* pos)
{
    unsigned long p = *pos;
    unsigned int count = size;

    if (p >= 512)
        return -1;
    if (count > 512)
        count = 512 - p;
    if (copy_to_user(buf, hello_buffer + p, count) != 0) {
        printk(KERN_ALERT "read error!\n");
        return -1;
    }

    return count;
}

static ssize_t hello_write(struct file* fp, const char __user* buf, size_t size, loff_t* pos)
{
    unsigned long p = *pos;
    unsigned int count = size;

    if (p >= 512)
        return -1;
    if (count > 512)
        count = 512 - p;
    if (copy_from_user(hello_buffer, buf + p, count) != 0) {
        printk(KERN_ALERT "write error!\n");
        return -1;
    }

    return count;
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .read = hello_read,
    .write = hello_write,
    .open = hello_open,
    .release = hello_release,
};

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello World! char module\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye! char module\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhuangzhuang Li <kaspersigi@outlook.com>");