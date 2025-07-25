#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	printk(KERN_INFO "HELLO KERNEL\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "BYE KERNEL\n");
}

module_init(hello_init);
module_exit(hello_exit);
