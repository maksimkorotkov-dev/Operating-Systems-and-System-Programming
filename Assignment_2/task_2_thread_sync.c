#include <stdio.h>
#include <pthread.h>

#define THREADS 4
#define ITERATIONS 1000000

long counter = 0;
pthread_mutex_t mutex;

void* increment_without_sync(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        counter++;
    }
    return NULL;
}

void* increment_with_mutex(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[THREADS];

    /* ---------- WITHOUT SYNCHRONIZATION ---------- */
    counter = 0;
    printf("Running WITHOUT synchronization...\n");

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_without_sync, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d\n", THREADS * ITERATIONS);
    printf("Actual:   %ld\n\n", counter);

    /* ---------- WITH MUTEX ---------- */
    counter = 0;
    pthread_mutex_init(&mutex, NULL);

    printf("Running WITH mutex synchronization...\n");

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_with_mutex, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d\n", THREADS * ITERATIONS);
    printf("Actual:   %ld\n", counter);

    pthread_mutex_destroy(&mutex);
    return 0;
}
