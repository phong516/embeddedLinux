#include "linux/export.h"
#include "linux/kern_levels.h"
#include "linux/printk.h"
#include "linux/types.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int gi_device_file_major_number = 0;
static const char gs_device_name[] = "Hello-Driver";

static const char gs_data[] = "HELLO";
static const ssize_t gi_data_size = sizeof(gs_data);

static ssize_t device_file_read(struct file *, char *, size_t, loff_t *);
static int my_init(void);
static void my_exit(void);

static struct file_operations driver_fops =
{
	.owner = THIS_MODULE,
	.read = device_file_read,
};

static int my_init(void)
{
	int result = 0;
	printk(KERN_NOTICE "Register device\n");
	result = register_chrdev(0, gs_device_name, &driver_fops);
	if (result < 0)
	{
		printk(KERN_WARNING "Can not register device\n");
		return result;
	}
	gi_device_file_major_number = result;
	printk(KERN_NOTICE "Registered device with major number = %i\n", gi_device_file_major_number);
	
	
	return result;
}

static void my_exit(void)
{
	printk(KERN_NOTICE "unregister_device() is called\n");
	if (gi_device_file_major_number < 0)
	{
		unregister_chrdev(gi_device_file_major_number, gs_device_name);
	}
	return;
}

static ssize_t device_file_read(struct file * file_ptr, char __user * user_buffer, size_t len, loff_t * pos)
{
	printk(KERN_NOTICE "Device file is read at offset %l, count %l", *pos, len);	
	if (*pos >= gi_data_size)
	{
		return 0;
	}
	if (*pos + len > gi_data_size)
	{
		len = gi_data_size - *pos;
	}
	if (copy_to_user(user_buffer, gs_data, len) != 0)
	{
		return -1;
	}
	/**pos += len;*/
	return 0;
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("PhongNL");
MODULE_DESCRIPTION("Hello chrdev");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
