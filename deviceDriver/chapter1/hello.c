#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello world\n");
	printk(KERN_INFO "Init: The current process is \"%s\" (%i)\n", 
						current->comm, current->pid);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye world\n");
	printk(KERN_INFO "Exit: The current process is \"%s\" (%i)\n", 
						current->comm, current->pid);
}

module_init(hello_init);
module_exit(hello_exit);

