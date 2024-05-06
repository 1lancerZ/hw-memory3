#include <linux/module.h>
#include <asm/io.h>
#include <linux/ioport.h>

MODULE_LICENSE("GPL");

struct resource * myMemRegion;

static int __init mem_module_init(void){
	printk(KERN_INFO "Start request men region!\n");

	myMemRegion = request_mem_region(994115584, 128, "vm");

	if(myMemRegion != NULL){
		printk(KERN_INFO "it's ok for %lld .", myMemRegion->start);
	}
	else{
		printk(KERN_ERR "Failed to request mem region!\n");
	}

	return 0;
}

static void __exit mem_module_exit(void){
	release_mem_region(994115584, 128);
	printk(KERN_INFO "Exit request_mem_region!\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
