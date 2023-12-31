 #include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 100 // Maximum size for matrices and buffer

// Global variables
int B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE], A[MAX_SIZE][MAX_SIZE];
int T[MAX_SIZE]; // Buffer
int n1, m1, n2, m2; // Dimensions of matrices B and C
int N; // Size of the buffer
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);
void insert_result(int row, int result);

int main() {
    // Initialize matrices and buffer size
    n1 = m1 = 3;
    n2 = m2 = 3;
    N = n1; // Buffer size is equal to the number of rows in matrix B

    // Initialize synchronization objects
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Generate random values for matrices B
    srand(time(NULL)); // Seed for random number generation
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            B[i][j] = rand() % 10 + 1; // Random values between 1 and 10
        }
    }

    // Generate random values for matrices C
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            C[i][j] = rand() % 10 + 1; // Random values between 1 and 10
        }
    }

    // Print matrices B and C for verification
    printf("Matrix B:\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("Matrix C:\n");
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy synchronization objects
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void insert_result(int row, int result) {
    T[row] = result;
}

void *producer(void *arg) {
    for (int i = 0; i < n1; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Calculate the ith row of matrix A
        int result = 0;
        for (int j = 0; j < m2; j++) {
            for (int k = 0; k < n2; k++) {
                result += B[i][k] * C[k][j];
            }
            A[i][j] = result; // Store the result in matrix A
            insert_result(i, result); // Insert the result into the buffer
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < n1; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Consume the result from the buffer and place it in matrix A
        int result = T[i];
        A[i][result] = result;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
} 
