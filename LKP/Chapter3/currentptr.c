#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/tty.h>

void tty_write_message1(struct tty_struct *tty, char *msg)
{
        if (tty && tty->driver->ops->write)
                tty->driver->ops->write(tty, msg, strlen(msg));
}


static int my_init(void)
{
        char *msg = "Hello tty!";
        printk("Hello, from the kernel...\n");
        printk("parent pid = %d(%s)\n", current->parent->pid, current->parent->comm);
        printk("current pid = %d(%s)\n", current->pid, current->comm);
        tty_write_message1(current->signal->tty, msg);
        return 0;
}


static void my_cleanup(void)
{
        printk("Goodbye, from the kernel...\n");
}

module_init(my_init);
module_exit(my_cleanup);

