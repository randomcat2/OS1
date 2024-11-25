#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; 

sem_t empty, full;
pthread_mutex_t buffer_mutex;


void* producer(void* arg) {
    int item = rand() % 100;
    printf("Produced %d\n", item);

    sem_wait(&empty); 
    pthread_mutex_lock(&buffer_mutex); 

    buffer[count] = item; 
    count++; 

    pthread_mutex_unlock(&buffer_mutex); 
    sem_post(&full); 

    return NULL;
}


void* consumer(void* arg) {
    sem_wait(&full); 
    pthread_mutex_lock(&buffer_mutex); 

    int item = buffer[0]; 
    printf("Consumed %d\n", item);

 
    for (int i = 0; i < count - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    buffer[count - 1] = 0; 
    count--; 

    pthread_mutex_unlock(&buffer_mutex); 
    sem_post(&empty); 

    return NULL;
}


void displayBuffer() {
    printf("Buffer: ");
    pthread_mutex_lock(&buffer_mutex); 
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]); 
    }
    pthread_mutex_unlock(&buffer_mutex); 
    printf("\n");
}

int main() {
    int choice;
    pthread_t prod_thread, cons_thread;

    
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0); 
    pthread_mutex_init(&buffer_mutex, NULL);

   
    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Start Producer\n");
        printf("2. Start Consumer\n");
        printf("3. Display Buffer\n");
        printf("4. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Start a producer thread
                pthread_create(&prod_thread, NULL, producer, NULL);
                pthread_join(prod_thread, NULL);
                break;
            case 2:
                // Start a consumer thread
                pthread_create(&cons_thread, NULL, consumer, NULL);
                pthread_join(cons_thread, NULL);
                break;
            case 3:
                // Display the buffer
                displayBuffer();
                break;
            case 4:
                // Cleanup and exit
                printf("Exiting program.\n");
                sem_destroy(&empty);
                sem_destroy(&full);
                pthread_mutex_destroy(&buffer_mutex);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}