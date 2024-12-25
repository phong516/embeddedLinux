#include "linux/export.h"
#include "linux/fs.h"
#include "linux/printk.h"
#include "linux/types.h"
#include <linux/init.h>

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
}

int __init hello_init(void)
{
	pr_info("INIT");	
	return 0;
}

void __exit hello_exit(void)
{
	pr_info("EXIT");
}
