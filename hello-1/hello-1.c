#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void) {
    pr_info("Hello world 1.\n");
    return 0;
}

void cleanup_module(void) {
    pr_info("Goodbyte world 1.\n");

}

MODULE_LICENSE("GPL");
