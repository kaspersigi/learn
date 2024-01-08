#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

static char hello_buffer[512] = { 0 };

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye!\n");
}

static int hello_open(struct inode* inode, struct file* fp)
{
    return 0;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhuangzhuang Li <kaspersigi@outlook.com>");