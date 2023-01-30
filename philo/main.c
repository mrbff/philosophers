#include "philo.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 4

typedef struct Task {
    void (*taskFunction)(int, int);
    int arg1, arg2;
} Task;

Task taskQueue[256];
int taskCount = 0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void sum(int a, int b) {
    usleep(50000);
    int sum = a + b;
    printf("Sum of %d and %d is %d\n", a, b, sum);
}

void product(int a, int b) {
    usleep(50000);
    int prod = a * b;
    printf("Product of %d and %d is %d\n", a, b, prod);
}

void executeTask(Task* task) {
    task->taskFunction(task->arg1, task->arg2);
    // usleep(50000);
    // int result = task->a + task->b;
    // printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}

void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void* startThread(void* args) {
    while (1) {
        Task task;

        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0) {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        task = taskQueue[0];
        int i;
        for (i = 0; i < taskCount - 1; i++) {
            taskQueue[i] = taskQueue[i + 1];
        }
        taskCount--;
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) {
            perror("Failed to create the thread");
        }
    }

    srand(time(NULL));
    for (i = 0; i < 100; i++) {
        Task t = {
            .taskFunction = i % 2 == 0 ? &sum : &product,
            .arg1 = rand() % 100,
            .arg2 = rand() % 100
        };
        submitTask(t);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    return 0;
}

/*
int	main(int ac, char **ac)
{
	t_param	philo;

	ft_check(ac, av, &philo);

}*/
/*
void	*eat(void	*arg)
{
	
}

void	*sleep()

void	*repeat()
*/
/*
int	main(int ac, char **av)
{
	pthread_t *ph;

	ph = phialloc();

	i = -1;
	while (++i < nphi)
	{
//		if (pthread_create(&ph[i], NULL /where return, &eat, NULL /arg/*))
			ft_putstr_fd("Failed to create thread\n", 2);
	}
	i = -1;
	while (++i < nphi)
	{
		if (pthread_join(ph[i], NULL))
			ft_putstr_fd("Failed to join thread\n", 2);
	}
}*/
