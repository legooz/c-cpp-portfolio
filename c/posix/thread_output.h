#ifndef THREAD_OUTPUT_H
#define THREAD_OUTPUT_H
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sem_t output_lock;
static int worker_failure;
static const char message[] = "output--------------------output\n";

static void *routine(void *argument) {
    const int synchronized = *(const int *)argument;
    if (synchronized) {
        while (sem_wait(&output_lock) < 0) {
            if (errno == EINTR) continue;
            perror("sem_wait");
            return &worker_failure;
        }
    }
    int failed = 0;
    for (const char *p = message; *p; ++p) {
        if (putc(*p, stdout) == EOF) { failed = 1; break; }
    }
    if (synchronized && sem_post(&output_lock) < 0) { perror("sem_post"); failed = 1; }
    return failed ? &worker_failure : NULL;
}

static int run_threads(int synchronized) {
    enum { THREAD_COUNT = 20 };
    pthread_t threads[THREAD_COUNT];
    int created = 0;
    int failed = 0;
    if (synchronized && sem_init(&output_lock, 0, 1) < 0) { perror("sem_init"); return 1; }
    for (; created < THREAD_COUNT; ++created) {
        int error = pthread_create(&threads[created], NULL, routine, &synchronized);
        if (error) { fprintf(stderr, "pthread_create: %s\n", strerror(error)); failed = 1; break; }
    }
    for (int i = 0; i < created; ++i) {
        void *result;
        int error = pthread_join(threads[i], &result);
        if (error) {
            /* Do not destroy shared state if a worker might still use it. */
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            exit(EXIT_FAILURE);
        }
        if (result) failed = 1;
    }
    if (synchronized && sem_destroy(&output_lock) < 0) { perror("sem_destroy"); failed = 1; }
    if (fflush(stdout) == EOF) failed = 1;
    return failed;
}
#endif
