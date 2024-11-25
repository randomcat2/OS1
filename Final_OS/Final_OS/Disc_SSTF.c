#include <stdio.h>
#include <stdlib.h>

// Function to calculate SSTF Disk Scheduling
void calculate(int requests[], int n, int initial_head) {
    int totalseektime = 0;
    int visited[n];
    int currentHead = initial_head;
    int count = 0;

    // Initialize all requests as unvisited
    for (int i = 0; i < n; ++i) {
        visited[i] = 0;
    }

    // Print table header
    printf("\nDisk Scheduling using SSTF Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. | Request | Seek Time |\n");
    printf("------------------------------------------------\n");

    // Process requests using SSTF
    while (count < n) {
        int minseektime = 10000; // Large initial value
        int minindex = -1;

        // Find the nearest unvisited request
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int seek_time = abs(requests[i] - currentHead);
                if (seek_time < minseektime) {
                    minseektime = seek_time;
                    minindex = i;
                }
            }
        }

        // Update total seek time and mark request as visited
        if (minindex != -1) {
            totalseektime += minseektime;
            printf("| %11d | %7d | %9d |\n", count + 1, requests[minindex], minseektime);
            currentHead = requests[minindex];
            visited[minindex] = 1;
            count++;
        }
    }

    // Print total seek time
    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalseektime);
}

int main() {
    int n, head;

    // Input number of requests and initial head position
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Input the disk requests
    printf("Enter disk requests:\n");
    for (int i = 0; i < n; ++i) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Call the SSTF scheduling function
    calculate(requests, n, head);

    return 0;
}
