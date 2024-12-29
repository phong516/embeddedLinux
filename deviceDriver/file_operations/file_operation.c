#include "linux/device.h"
#include "linux/device/class.h"
#include "linux/err.h"
#include "linux/export.h"
#include "linux/fs.h"
#include "linux/gfp.h"
#include "linux/printk.h"
#include "linux/types.h"
#include "linux/uaccess.h"
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/slab.h>

#define g_mem_size 1024

static char * g_kernel_buffer;

static dev_t hello_dev;
static struct class * hello_class;
static struct cdev hello_cdev;

static int __init hello_init(void);
static void __exit hello_exit(void);
static ssize_t hello_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t hello_write(struct file *, const char __user *, size_t, loff_t *);
static int hello_ioctl(struct inode *, struct file *, unsigned int, unsigned long);
static int hello_open(struct inode *, struct file *);
static int hello_release(struct inode *, struct file *);

static struct file_operations hello_fops = 
{
		.owner = THIS_MODULE,
		.read = hello_read,
		.write = hello_write,
		.open = hello_open,
		.release = hello_release,
};

int __init hello_init(void)
{
	pr_info("INIT\n");	
	if (alloc_chrdev_region(&hello_dev, 0, 1, "hello-chrdev") < 0)
	{
		pr_err("Can not alloc new chrdev\n");
		return -1;
	}

	cdev_init(&hello_cdev, &hello_fops);
	
	if (cdev_add(&hello_cdev, hello_dev, 1) < 0)			
	{
		pr_err("Can not add cdev\n");
		goto label_remove_chrdev;
	}
	
	hello_class = class_create(THIS_MODULE, "hello-class");
	if (IS_ERR(hello_class))
	{
		pr_err("Can not create class\n");
		goto label_remove_cdev;	
	}
	if (IS_ERR(device_create(hello_class, NULL, hello_dev, NULL, "hello-dev")))
	{
		pr_err("Can not create device\n");
		goto label_remove_class;
	}

	g_kernel_buffer = kmalloc(g_mem_size, GFP_KERNEL);
	if (g_kernel_buffer == NULL)
	{
		pr_err("Can not malloc new size\n");
		goto label_remove_device;
	}
	memset(g_kernel_buffer, 0, g_mem_size);
	strcpy(g_kernel_buffer, "HELLO WORLD Fops\n");
	
	return 0;

label_remove_device:
	device_destroy(hello_class, hello_dev);
label_remove_class:
	class_destroy(hello_class);
label_remove_cdev:
	cdev_del(&hello_cdev);
label_remove_chrdev:
	unregister_chrdev_region(hello_dev, 1);
	return -1;
	
}
void __exit hello_exit(void) {
	pr_info("EXIT\n");
	kfree(g_kernel_buffer);
	device_destroy(hello_class, hello_dev);
	class_destroy(hello_class);
	cdev_del(&hello_cdev);
	unregister_chrdev_region(hello_dev, 1);
}

static ssize_t hello_read(struct file * file, char __user * buff, size_t len, loff_t * pos)
{
	pr_info("HELLO READ\n");
	ssize_t bytes = len < (g_mem_size - (*pos)) ? len : (g_mem_size - (*pos));
	if (copy_to_user(buff, g_kernel_buffer, bytes))
	{
		return -EFAULT;
	}
	(*pos) += bytes;
	return bytes;
}

static ssize_t hello_write(struct file *file, const char __user * buff, size_t len, loff_t * pos)
{
	pr_info("HELLO WRITE\n");
	pr_info("Len %i, Pos %lli\n", len, *pos);
	if ((*pos) < sizeof(g_kernel_buffer))
	{
		memset(g_kernel_buffer + (*pos) + len, '\0', g_mem_size - (*pos) - len);
	}
	if(copy_from_user(g_kernel_buffer + (*pos), buff, len) != 0)
	{
		pr_err("Can not write data\n");
		return -EFAULT;
	}
	(*pos) += len;
	return len;
}
static int hello_ioctl(struct inode * hello_inode, struct file * hello_file, unsigned int hello_int, unsigned long hello_long)
{
	pr_info("HELLO IOCTL\n");
	return 0;
}
static int hello_open(struct inode * hello_inode, struct file * hello_file)
{
	pr_info("HELLO OPEN\n");
	return 0;
}
static int hello_release(struct inode * hello_inode, struct file * hello_file)
{
	pr_info("HELLO RELEASE\n");
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("PhongNL <tiphong113@gmail.com>");
MODULE_DESCRIPTION("Hello world file operations");
MODULE_VERSION("0:1.0");
