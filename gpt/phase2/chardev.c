#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "chardev"

static int open(struct inode *, struct file *);
static int release(struct inode *, struct file *);
static ssize_t write(struct file *, const char __user *, size_t, loff_t *);
static ssize_t read(struct file *, char __user *, size_t, loff_t *);

static struct cdev g_cdev;
static dev_t g_dev;
static struct class * g_class;
static struct device * g_device;

#define BUFFER_LEN 256
static size_t g_buffer_len = 0;
static char g_kernel_buffer[BUFFER_LEN] = {'\0'};

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = open,
	.release = release,
    .write = write,
    .read = read,
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

static ssize_t write(struct file * p_file, const char __user * c_buffer, size_t size, loff_t * l_offset)
{
	printk(KERN_INFO "size: %zu, l_offset: %llu\n", size, *l_offset);	
	if (size > BUFFER_LEN)
	{
		size = BUFFER_LEN - 1;
	}
    if (copy_from_user(g_kernel_buffer, c_buffer, size))
	{
		return -EFAULT;
	}

    g_kernel_buffer[size] = '\0';
    g_buffer_len = size;
    printk(KERN_INFO "CHARDEV: Write %s\n", g_kernel_buffer);
    return size;
}

static ssize_t read(struct file * p_file, char __user * c_buffer, size_t size, loff_t * l_offset)
{
	printk(KERN_INFO "CHARDEV: size: %zu, len: %zu, l_offset: %lld\n", size, g_buffer_len, *l_offset);

	if (g_buffer_len == 0)
	{
		return 0;
	}

	if (size > g_buffer_len - *l_offset)
	{
		size = g_buffer_len - *l_offset;
	}
	if (copy_to_user(c_buffer, g_kernel_buffer + *l_offset, size))
	{
		return -EFAULT;
	}
	*l_offset += size;
    	printk(KERN_INFO "CHARDEV: l_offset: %lld, read %s\n", *l_offset, c_buffer);
	return *l_offset >= g_buffer_len ? 0 : size;
}
