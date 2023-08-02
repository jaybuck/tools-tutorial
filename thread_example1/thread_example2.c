/* Thread example */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *data);

int main(void)
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, worker, "X");
    pthread_create(&th2, NULL, worker, "Y");
    sleep(5);
    printf("Exiting from main program\n");
    return 0;
}

void *worker(void *data)
{
    char *name = (char*)data;

    for (int i = 0; i < 20; i++)
    {
        usleep(50000);
        printf("Hi from thread name = %s\n", name);
    }

    printf("Thread %s done!\n", name);
    return NULL;
}



