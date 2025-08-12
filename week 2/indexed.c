#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct IndexBlock {
    int data_blocks[MAX_BLOCKS];
};

// Initialize all blocks to -1 (unallocated)
void initializeIndexBlock(struct IndexBlock* indexBlock) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        indexBlock->data_blocks[i] = -1;
    }
}

// Allocate a data block into the next available slot
int allocateDataBlock(struct IndexBlock* indexBlock, int blockNumber) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (indexBlock->data_blocks[i] == -1) {
            indexBlock->data_blocks[i] = blockNumber;
            return 1;
        }
    }
    return 0; // No space left
}

// Read a specific block
void readData(struct IndexBlock* indexBlock, int fileBlockNumber) {
    int flag = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (indexBlock->data_blocks[i] == fileBlockNumber) {
            printf("Reading data from block %d\n", fileBlockNumber);
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("Block %d is not allocated.\n", fileBlockNumber);
    }
}

// Display the File Allocation Table in formatted style
void displayFileAllocationTable(struct IndexBlock* indexBlock) {
    printf("\n+-------+------------+\n");
    printf("| Index | Data Block |\n");
    printf("+-------+------------+\n");
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (indexBlock->data_blocks[i] != -1) {
            printf("| %5d | %10d |\n", i, indexBlock->data_blocks[i]);
        }
    }
    printf("+-------+------------+\n");
}

int main() {
    struct IndexBlock indexBlock;
    initializeIndexBlock(&indexBlock);

    int n;
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int block;
        printf("Enter block number to allocate: ");
        scanf("%d", &block);

        if (block < 0 || block >= MAX_BLOCKS) {
            printf("Invalid block number. Please enter a number between 0 and %d.\n", MAX_BLOCKS - 1);
            i--; // Retry the current iteration
            continue;
        }

        if (!allocateDataBlock(&indexBlock, block)) {
            printf("No space left in index block.\n");
            break;
        }
    }

    // Display allocation table after all blocks are allocated
    displayFileAllocationTable(&indexBlock);

    // Reading phase
    char choice;
    do {
        int readBlock;
        printf("\nEnter block number to read: ");
        scanf("%d", &readBlock);
        readData(&indexBlock, readBlock);

        printf("Do you want to read another block? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

