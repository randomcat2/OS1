#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;
pthread_mutex_t mutex;
int read_count = 0;
int data = 0; // Shared data

void *writer(void *arg) {
    sem_wait(&wrt);
    data++;
    printf("Writer %d modified data to %d\n", *((int *)arg), data);
    sem_post(&wrt);
    return NULL;
}

void *reader(void *arg) {
    pthread_mutex_lock(&mutex);
    read_count++;
    printf("Reader %d started reading. Read count: %d\n", *((int *)arg), read_count);
    if (read_count == 1) {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d read data as %d\n", *((int *)arg), data);

    pthread_mutex_lock(&mutex);
    read_count--;
    printf("Reader %d finished reading. Read count: %d\n", *((int *)arg), read_count);
    if (read_count == 0) {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t read[5], write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int a[5] = {1, 2, 3, 4, 5}; // Just to identify readers and writers

    for (int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, &a[i]);
        pthread_create(&read[i], NULL, reader, &a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
        pthread_join(read[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}