#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define PHILOSOPHERS 5
#define EATING_TIME 3

pthread_mutex_t chopstick[PHILOSOPHERS];

void *philosopher(void *philosopher_num) {
    int philosopher_id = *(int *)philosopher_num;
    struct timeval tp;

    while (1) {
        gettimeofday(&tp, NULL);
        printf("Philosopher %d is thinking at %ld\n", philosopher_id, tp.tv_sec);

        pthread_mutex_lock(&chopstick[philosopher_id]);
        pthread_mutex_lock(&chopstick[(philosopher_id + 1) % PHILOSOPHERS]);

        gettimeofday(&tp, NULL);
        printf("Philosopher %d is eating at %ld\n", philosopher_id, tp.tv_sec);

        usleep(EATING_TIME * 1000000);

        pthread_mutex_unlock(&chopstick[philosopher_id]);
        pthread_mutex_unlock(&chopstick[(philosopher_id + 1) % PHILOSOPHERS]);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int i;
    pthread_t philosopher_thread[PHILOSOPHERS];
    int philosopher_num[PHILOSOPHERS];

    memset(philosopher_num, 0, sizeof(philosopher_num));

    for (i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    for (i = 0; i < PHILOSOPHERS; i++) {
        philosopher_num[i] = i;
        pthread_create(&philosopher_thread[i], NULL, philosopher, &philosopher_num[i]);
        pthread_detach(philosopher_thread[i]);
    }

    while (1) {
        usleep(100);
    }

    return 0;
}

