#include <stdio.h>
#include <stdlib.h>
#include "emalloc.h"

#define SIZE_4KB 4 * 1024
#define SIZE_1MB 1024 *1024
#define SIZE_4MB 4*1024 *1024

void infoFreeBlock(){
	FreeBlock *curr=free_list;
	int i = 1;
	while(curr != NULL){
		printf("FreeBlock%d address: %p,size: %d\n", i, curr, curr->size);
		i += 1;
		curr = curr->next;
	}
}
int main() {
	// 初始化内存管理器
	initialize_memory();

	// 测试分配和释放内存
	void *p1 = emalloc(SIZE_1MB);
	printf("Allocated memory at address:%p\n", p1);
	void *p2 = emalloc(SIZE_1MB);
	printf("Allocated memory at address: %p\n", p2);
	efree(p1);
	printf("Freed memory at address: %p\n", p1);

	infoFreeBlock();

	void *p3=emalloc(SIZE_4MB);
	printf("Allocated memory at address: %p\n", p3);
	void *p4=emalloc(SIZE_4KB);
	printf("Allocated memory at address: %p\n", p4);
	
	infoFreeBlock();

	efree(p2);
	printf("Freed memory at address: %p\n", p2);
	efree(p3);
	printf("Freed memory at address: %p\n", p3);
	efree(p4);
	printf("Freed memory at address: %p\n", p4);
	
	infoFreeBlock();

	return 0;
}
