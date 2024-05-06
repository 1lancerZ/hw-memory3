#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define MEMORY_SIZE (256 * 1024 * 1024) // 256MB 内存块大小

typedef struct FreeBlock {
    size_t size; // 空闲内存块的大小
    struct FreeBlock *next; // 指向下一个空闲内存块的指针
} FreeBlock;

unsigned char memory_pool[MEMORY_SIZE]; // 内存池
FreeBlock *free_list = NULL; // 空闲内存块链表

void initialize_memory() {
    // 将整个内存池视为一个大的空闲内存块
    FreeBlock *block = (FreeBlock *)malloc(sizeof(memory_pool));
    if (block == NULL) {
        printf("Failed to allocate memory for free block\n");
        exit(1);
    }
    block->size = MEMORY_SIZE;
    block->next = NULL;
    free_list = block;
}

void *emalloc(size_t size) {
    FreeBlock *prev = NULL;
    FreeBlock *curr = free_list;

    while (curr != NULL) {
        if (curr->size >= size) {
            // 找到一个大小满足要求的空闲内存块
            if (curr->size > size) {
                // 如果当前空闲内存块大于所需大小，则将剩余部分插入到链表中
                FreeBlock *new_block = (FreeBlock *)((unsigned char *)curr + size);
                new_block->size = curr->size - size;
                new_block->next = curr->next;
                if (prev == NULL) {
                    free_list = new_block;
                } else {
                    prev->next = new_block;
                }
            } else {
                // 如果当前空闲内存块大小与所需大小相同，则将其从链表中移除
                if (prev == NULL) {
                    free_list = curr->next;
                } else {
                    prev->next = curr->next;
                }
            }
	    //分配后的curr的size改为分配的内存大小，为释放做准备
	    curr->size = size;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }

    // 没有足够大小的空闲内存块
    return NULL;
}

void efree(void *ptr) {
    FreeBlock *block = (FreeBlock *)ptr;

    // 在释放内存时，我们将内存块重新插入到链表的合适位置
    FreeBlock *prev = NULL;
    FreeBlock *curr = free_list;

    while (curr != NULL && curr < block) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        // 如果释放的内存块位于链表头部
        block->next = free_list;
        free_list = block;
    } else {
        // 如果释放的内存块位于链表中间或尾部
        block->next = prev->next;
        prev->next = block;
    }

    // 检查释放的内存块是否与相邻的空闲内存块合并
    merge_free_blocks();
}

void merge_free_blocks() {
    FreeBlock *prev = NULL;
    FreeBlock *curr = free_list;

    while (curr != NULL && curr->next != NULL) {
	//printf("address: %p, size: %d\n",curr,curr->size);
        if ((unsigned char *)curr + curr->size == (unsigned char *)curr->next) {
            // 如果相邻的空闲内存块，则合并它们
            curr->size += curr->next->size;
            curr->next = curr->next->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}


