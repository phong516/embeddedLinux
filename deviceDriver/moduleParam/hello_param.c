#include "linux/printk.h"
#include "linux/stat.h"
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/module.h>

int g_value, g_cb_value;

/*module_param(g_value, int, S_IRWXU);*/

int notify_param(const char * val, const struct kernel_param * kp)
{
	int result = param_set_int(val, kp); 
	if (result == 0)
	{
		pr_info("Call back\n");
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops = 
{
		.set = notify_param,
		.get = param_get_int,
};

module_param_cb(g_value, &my_param_ops, &g_cb_value, S_IRWXU);

static int __init hello_init(void)
{
	pr_info("Init successfully\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Exit successfully\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PhongNL <tiphong113@gmail.com>");
MODULE_DESCRIPTION("Hello module param");
MODULE_VERSION("0:0.1");
