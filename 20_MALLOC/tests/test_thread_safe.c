#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 8
#define NUM_ALLOCATIONS 10

void *thread_function(void *arg) {
    size_t id = (size_t)arg;
    void *allocated[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        allocated[i] = malloc(rand() % 1024 + 1); // Allocation aléatoire
        if (!allocated[i]) {
            fprintf(stderr, "Thread %zu: malloc failed\n", id);
            pthread_exit(NULL);
        }

        if (rand() % 2 == 0) {
            allocated[i] = realloc(allocated[i], rand() % 2048 + 1);
        }

        if (rand() % 4 == 0) {
            free(allocated[i]);
            allocated[i] = NULL;
        }
    }

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        if (allocated[i]) {
            free(allocated[i]);
        }
    }

    printf("Thread %zu finished successfully.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (size_t i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}
