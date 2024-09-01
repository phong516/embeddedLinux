#include <linux/module.h>
#include <linux/kernel.h>

int init_module()
{
  printk(KERN_INFO "Loaded\n");
  return 0;
}

void cleanup_module()
{
  printk(KEN_INFO "Unloaded\n");
}
