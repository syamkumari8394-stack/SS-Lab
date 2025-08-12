#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct Block {
    int block_number;
    struct Block* next;
};

struct Block* allocateBlock(int blockNumber) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->block_number = blockNumber;
    newBlock->next = NULL;
    return newBlock;
}

int main() {
    struct Block* head = NULL;
    struct Block* current = NULL;
    int n;

    printf("Enter number of blocks to allocate: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_BLOCKS) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int blockNum;
        printf("Enter block number %d: ", i + 1);
        scanf("%d", &blockNum);

        if (blockNum < 0 || blockNum >= MAX_BLOCKS) {
            printf("Invalid block number. Please enter between 0 and %d.\n", MAX_BLOCKS - 1);
            i--;
            continue;
        }

        struct Block* newBlock = allocateBlock(blockNum);

        if (head == NULL) {
            head = newBlock;
            current = head;
        } else {
            current->next = newBlock;
            current = current->next;
        }
    }

    printf("Allocated blocks: ");
    current = head;
    while (current != NULL) {
        printf("%d->", current->block_number);
        current = current->next;
    }
    printf("\n");

    current = head;
    while (current != NULL) {
        struct Block* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

