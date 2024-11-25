#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of integers to sort: ");
    scanf("%d", &n);

    int arr[n];
    int childArr[n];
    
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        childArr[i] = arr[i];  // Copy the array for the child process
    }

    pid_t pid = fork();  // Create a new child process

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) started.\n", getpid());
        sleep(2); // Sleep for 2 seconds to let the child process start

        printf("Parent process (PID: %d) sorting using insertion sort...\n", getpid());
        insertionSort(arr, n);
        printf("Parent process sorted array: ");
        printArray(arr, n);

        
        printf("\nDemonstrating Zombie State: Parent process sleeping for 10 seconds while child exits...\n");
        sleep(10); 

        wait(NULL);
        printf("Parent process (PID: %d) has finished waiting for child. Zombie state cleared.\n\n", getpid());

       printf("Parent process (PID: %d) exiting...\n", getpid());
        sleep(2); // Sleep to allow orphan state to be demonstrated

    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d, Parent PID: %d) started.\n", getpid(), getppid());
        printf("Child process sorting using insertion sort...\n");
        insertionSort(childArr, n);
        printf("Child process sorted array: ");
        printArray(childArr, n);

        printf("Child process (PID: %d) finished sorting.\n", getpid());

        sleep(5);
        printf("\nDemonstrating Orphan State: Child process (PID: %d) continuing after parent exits...\n", getpid());

        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);

    } else {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}