#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES  50

struct File {
    char filename[20];
    int start_block;
    int num_blocks;
};

int main() {
    int blockStatus[MAX_BLOCKS] = {0};
    struct File files[MAX_FILES];
    int n;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char name[20];
        int start, length;
        printf("\nFile %d:\n", i + 1);
        printf("Enter file name: ");
        scanf("%s", name);
        printf("Enter starting block (0 to %d): ", MAX_BLOCKS - 1);
        scanf("%d", &start);
        printf("Enter number of blocks: ");
        scanf("%d", &length);

        if (start < 0 || start + length > MAX_BLOCKS) {
            printf("Error: Invalid block range. File not allocated.\n");
            i--;
            continue;
        }

        int isFree = 1;
        for (int j = start; j < start + length; j++) {
            if (blockStatus[j] == 1) {
                isFree = 0;
                break;
            }
        }

        if (!isFree) {
            printf("Error: Blocks already allocated. File not allocated.\n");
            i--;
            continue;
        }

        for (int j = start; j < start + length; j++) {
            blockStatus[j] = 1;
        }

        strcpy(files[i].filename, name);
        files[i].start_block = start;
        files[i].num_blocks = length;

        printf("File '%s' allocated from block %d to %d.\n", name, start, start + length - 1);
    }

    printf("\n\nFile Allocation Table:\n");

    printf("+-----------------+--------------+-----------------+\n");
    printf("| %-15s | %-12s | %-15s |\n", "Filename", "Start Block", "No. of Blocks");
    printf("+-----------------+--------------+-----------------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %-15s | %-12d | %-15d |\n",
               files[i].filename, files[i].start_block, files[i].num_blocks);
    }

    printf("+-----------------+--------------+-----------------+\n");

    return 0;
}

