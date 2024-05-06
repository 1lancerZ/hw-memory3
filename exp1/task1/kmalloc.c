#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

unsigned char *kmallocmem1;
unsigned char *kmallocmem2;

static int __init mem_module_init(void)
{
	printk("Start kmalloc!\n");
	//分配内存以字节为单位，flags为GFP_KERNEL表示正常分配内存
	kmallocmem1 = (unsigned char*)kmalloc(1024, GFP_KERNEL);
	//内存分配成功则打印地址
	if (kmallocmem1 != NULL){
		printk(KERN_ALERT "kmallocmem1 addr = %lx\n", (unsigned long)kmallocmem1);
	}else{
		printk("Failed to allocate kmallocmem1!\n");
	}
	kmallocmem2 = (unsigned char *)kmalloc(8192, GFP_KERNEL);
	if (kmallocmem2 != NULL){
		printk(KERN_ALERT "kmallocmem2 addr = %lx\n", (unsigned long)kmallocmem2);
	}else{
		printk("Failed to allocate kmallocmem2!\n");
	}
	return 0;
}

static void __exit mem_module_exit(void)
{
	//调用kfree函数释放内存
	kfree(kmallocmem1);
	kfree(kmallocmem2);
	printk("Exit kmalloc!\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
