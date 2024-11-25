#include <stdio.h>
#include <stdlib.h>

// Function to calculate SCAN Disk Scheduling
void calculateScan(int requests[], int n, int initial_head, int disk_size, int direction) {
    int totalseektime = 0;
    int currentHead = initial_head;

    // Sort the requests array in ascending order
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Print table header
    printf("\nDisk Scheduling using SCAN Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. | Request | Seek Time |\n");
    printf("------------------------------------------------\n");

    // Find the starting index for the current head position
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }

    // Process requests in the specified direction
    if (direction == 1) { // Moving towards higher values
        for (int i = start_index; i < n; ++i) {
            int seek_time = abs(requests[i] - currentHead);
            totalseektime += seek_time;
            printf("| %11d | %7d | %9d |\n", i - start_index + 1, requests[i], seek_time);
            currentHead = requests[i];
        }

        // Move to the disk's end
        int end_seek_time = disk_size - 1 - currentHead;
        totalseektime += end_seek_time;
        printf("|      -      | %7d | %9d |\n", disk_size - 1, end_seek_time);
        currentHead = disk_size - 1;

        // Process remaining requests on the way back
        for (int i = start_index - 1; i >= 0; --i) {
            int seek_time = abs(requests[i] - currentHead);
            totalseektime += seek_time;
            printf("| %11d | %7d | %9d |\n", start_index - i + n - 1, requests[i], seek_time);
            currentHead = requests[i];
        }
    } else { // Moving towards lower values
        for (int i = start_index - 1; i >= 0; --i) {
            int seek_time = abs(requests[i] - currentHead);
            totalseektime += seek_time;
            printf("| %11d | %7d | %9d |\n", start_index - i, requests[i], seek_time);
            currentHead = requests[i];
        }

        // Move to the disk's start
        int end_seek_time = currentHead;
        totalseektime += end_seek_time;
        printf("|      -      |       0 | %9d |\n", end_seek_time);
        currentHead = 0;

        // Process remaining requests on the way back
        for (int i = start_index; i < n; ++i) {
            int seek_time = abs(requests[i] - currentHead);
            totalseektime += seek_time;
            printf("| %11d | %7d | %9d |\n", i + 1, requests[i], seek_time);
            currentHead = requests[i];
        }
    }

    // Print total seek time
    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalseektime);
}

int main() {
    int n, head, direction, disk_size;

    // Input parameters
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 - right, 0 - left): ");
    scanf("%d", &direction);

    printf("Enter disk requests:\n");
    for (int i = 0; i < n; ++i) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Call the SCAN scheduling function
    calculateScan(requests, n, head, disk_size, direction);

    return 0;
}
