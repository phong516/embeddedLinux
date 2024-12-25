#include "linux/device/class.h"
#include "linux/err.h"
#include "linux/export.h"
#include "linux/printk.h"
#include "linux/types.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

static dev_t dev;
static struct class * hello_class = NULL;

static int __init hello_init(void)
{
	int result = alloc_chrdev_region(&dev, 0, 1, "HELLO NUMBER");
	if (result < 0)
	{
		pr_err("Can not alloc new chrdev\n");	
		return result;
	}
	pr_info("Allocated new chrdev with major %i, minor %i\n", MAJOR(dev), MINOR(dev));	
	hello_class = class_create(THIS_MODULE, "hello_class");
	if (IS_ERR(hello_class))
	{
		pr_err("Can not create class\n");
		goto label_class_err;
	}
	if (IS_ERR(device_create(hello_class, NULL, dev, NULL, "hello_dev")))
	{
		pr_err("Cannot create device\n");
		goto label_device_err;
	}
	return 0;

label_device_err:
	class_destroy(hello_class);
label_class_err:
	unregister_chrdev_region(dev, 1);
	return -1;
}

static void __exit hello_exit(void)
{
	device_destroy(hello_class, dev);
	class_destroy(hello_class);
	unregister_chrdev_region(dev, 1);
	pr_info("BYE\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PhongNL <tiphong113@gmail.com>");
MODULE_DESCRIPTION("Hello world major, minor number");
MODULE_VERSION("0:1.0");
