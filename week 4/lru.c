//**********************************************************
// C program -LRU page replacement algorithm.Simple Implementation
//***********************************************************
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Maximum number of frames
#define MAX_PAGES 20 // Maximum number of pages

int frames[MAX_FRAMES]; // Array to store the frames
int counter[MAX_FRAMES]; // Array to store the counter for each frame

// Function to initialize frames and counter arrays
void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initializing frames with -1 (empty)
        counter[i] = 0; // Initializing counter with 0
    }
}

// Function to display the frames
void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

// Function to find the least recently used frame
int findLRU() {
    int max = counter[0];
    int lru_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] > max) {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

// Function to implement LRU page replacement algorithm
void LRU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d is already there \n",page);
                break;
            }
        }

        if (!found) {
            int lru_frame = findLRU();
            printf("page %d is loaded in frame %d\n",page,lru_frame);
            frames[lru_frame] = page;
            counter[lru_frame] = 0;
            page_faults++;
        }

        // Increment counter for all frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            counter[j]++;
        }

        // Reset counter for the used frame
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                counter[j] = 0;
                break;
            }
        }

        //printf("Page %d : ", page);
        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES]; // Array to store pages

    // Example sequence of page references
    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    initialize(); // Initialize frames and counter arrays
    LRU(pages, n); // Apply LRU algorithm

    return 0;
}
