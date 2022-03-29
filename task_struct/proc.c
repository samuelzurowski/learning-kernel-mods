#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");


int process_init(void) {
    struct task_struct *task;
    struct task_struct *thread;
    char comm[TASK_COMM_LEN];

    for_each_process(task) {
        printk(KERN_INFO "Task %s (pid=%d)\n", task->comm, task_pid_nr(task));

	for_each_thread(task, thread) {
		printk(KERN_INFO "Task %s\t PPID=%d\t thread node: %p\t Name: %s\t T_PID:[%d]\t TGID:[%d]\n",
			task->comm, task_pid_nr(task), thread, get_task_comm(comm, thread), 
			task_pid_nr(thread), task_tgid_nr(thread));
	}

    }
    return 1;

}


static int __init proc_init(void) {
	printk(KERN_INFO "Enabling module PROC.ko\n");
	int i;
	
	i = process_init();

	printk(KERN_INFO "IS Good=%d", i);
	return 0;
}

static void __exit proc_exit(void) {
	printk(KERN_INFO "Exiting PROC.ko\n");
}

module_init(proc_init);
module_exit(proc_exit);
