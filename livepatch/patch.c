#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>

#include <linux/seq_file.h>


// replace function that is overriden.
static int livepatch_cmdline_proc_show(struct seq_file *m, void *v) {
	seq_printf(m, "%s\n", "this has been live patched sadge");
	return 0;
}

// the livepatch API has to be used with  astruct
// this indicates which kernel functions are being overriden
static struct klp_func funcs[] = {
	{
	.old_name = "cmdline_proc_show",
	.new_func = livepatch_cmdline_proc_show,
	
	}, { }

};

// The struct above gets passed as a field into the klp_object
// (kernel live patch object)...

static struct klp_object objs[] = {
	{
		// null mean vmlinux
		.funcs = funcs,
	
	}, { }
};

// again the struct now gets pass into klp_patch object.
// the address of this object in memory will be passed into klp_enable_patch function
static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};


static int livepatch_init(void) {
	return klp_enable_patch(&patch);
}

static void livepatch_exit(void) {}

module_init(livepatch_init);
module_exit(livepatch_exit);

MODULE_LICENSE("GPL");

MODULE_INFO(livepatch, "Y");
