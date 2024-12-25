#include "linux/printk.h"
#include "linux/types.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>

dev_t dev;

static int __init hello_init(void)
{
	int result = alloc_chrdev_region(&dev, 0, 1, "HELLO NUMBER");
	if (result == 0)
	{
		pr_info("HELLO\n");
	}
	else 
	{
		pr_err("Can not alloc new chrdev\n");	
	}
	return result;
}

static void __exit hello_exit(void)
{
	unregister_chrdev_region(dev, 1);
	pr_info("BYE\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PhongNL <tiphong113@gmail.com>");
MODULE_DESCRIPTION("Hello world major, minor number");
MODULE_VERSION("0:1.0");
