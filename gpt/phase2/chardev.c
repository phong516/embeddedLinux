#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "chardev"

static int open(struct inode *, struct file *);
static int release(struct inode *, struct file *);

static struct cdev g_cdev;
static dev_t g_dev;
static struct class * g_class;
static struct device * g_device;
static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = open,
	.release = release,
};

static int __init chardev_init(void)
{
	int ret = alloc_chrdev_region(&g_dev, 0, 1, DEVICE_NAME);
	if (ret < 0)
	{
		printk(KERN_ERR "CHARDEV: Cannot alloc chrdev region!!!\n");
		goto alloc_fail;
	}
	cdev_init(&g_cdev, &fops);	
	cdev_add(&g_cdev, g_dev, 1);
	
	g_class = class_create(DEVICE_NAME);
	if (IS_ERR(g_class))
	{
		ret = PTR_ERR(g_class);
		printk(KERN_ERR "CHARDEV: Cannot create g_class!!!\n");
		goto reg_fail;
	}
	g_device = device_create(g_class, NULL, g_dev, NULL, DEVICE_NAME);
	if (IS_ERR(g_device))
	{
		ret = PTR_ERR(g_device);
		printk(KERN_ERR "CHARDEV: Cannot create device!!!\n");
		goto dev_fail;
	}

	printk(KERN_INFO "CHARDEV: INIT\n");
	return 0;

dev_fail:
	class_destroy(g_class);
	cdev_del(&g_cdev);
reg_fail:
	unregister_chrdev_region(g_dev, 1);
alloc_fail:
	return ret;
}

static void __exit chardev_exit(void)
{
	device_destroy(g_class, g_dev);
	class_destroy(g_class);
	cdev_del(&g_cdev);
	unregister_chrdev_region(g_dev, 1);
    	printk(KERN_INFO "CHARDEV: EXIT\n");
}

module_init(chardev_init);
module_exit(chardev_exit);

static int open(struct inode * p_inode, struct file * p_file)
{
	printk(KERN_INFO "CHARDEV: Open\n");
	return 0;
}
static int release(struct inode * p_inode, struct file * p_file)
{
	printk(KERN_INFO "CHARDEV: Release\n");
	return 0;
}

