#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

static int status = 0;
module_param(status, int, 0660);

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Zhuangzhuang Li <kaspersigi@outlook.com>");