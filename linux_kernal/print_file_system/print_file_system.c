#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/init.h>

#define FILE_SYSTEMS_LOCK 0xffffffff81a80b58
#define FILE_SYSTEMS      0xffffffff81fa6c80

static int __init fs_init(void)
{
    struct file_system_type **tmp;

    read_lock((rwlock_t *)FILE_SYSTEMS_LOCK);
    tmp = (struct file_system_type **)FILE_SYSTEMS;
    printk("input fs_type from kernel\n");
    while(*tmp){
        printk("fs_name: %s\n",(*tmp)->name);
        tmp = &(*tmp)->next;
    }
    read_unlock((rwlock_t *)FILE_SYSTEMS_LOCK);
    return 0;
}

static void __exit fs_exit(void)
{
    printk("fs exit...\n");
}

module_init(fs_init);
module_exit(fs_exit);
MODULE_LICENSE("GPL");
