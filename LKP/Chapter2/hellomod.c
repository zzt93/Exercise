#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hellomod_init(void)
{
        printk("<1>Hello, World! form the kernel space...\n");
        return 0;
}

static void __exit hellomod_cleanup(void)
{
        printk("<1>Goodbye, World! leaving kernel space...\n");
}

module_init(hellomod_init);
module_exit(hellomod_cleanup);
