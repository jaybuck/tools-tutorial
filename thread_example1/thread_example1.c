/* Thread example */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *data);

#define NUMTHREADS 4
pthread_t threads[NUMTHREADS];

int main(void)
{
    int *index_ptr;

    for(int i = 0; i < NUMTHREADS; i++) {
        index_ptr = (int *) malloc(sizeof(int));
        *index_ptr = i;
        pthread_create(&threads[i], NULL, worker, (void *)index_ptr);
    }

    sleep(5);
    pthread_join(threads[0], NULL);  
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
  
    printf("Exiting from main program\n");
    return 0;
}

/* You could do something interesting/useful in the worker funciton.
 * Like count how many times each character occurs,
 * each word occurs, etc.
*/
void *worker(void *data)
{
    int *int_p = (int *)data;
    int indx = *int_p;
    char fname[80];
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    // Build filename
    sprintf(fname, "part_%d.txt", indx);
    printf("Worker started. Reading file: %s\n", fname);

    FILE *stream = fopen(fname, "r");
    if(stream == NULL) {
        fprintf(stderr, "Unable to open file: %s\n", fname);
        exit(1);
    }

    int nlines = 0;
    while ((nread = getline(&line, &len, stream)) != -1) {
        nlines++;
        printf("Thread: %d : Line %d : Read line of length %zd:\n", indx, nlines, nread);
        // fwrite(line, nread, 1, stdout);
        if (nlines > 20) {
            break;
        }
    }

    free(line);
    fclose(stream);

    printf("Thread %d done!\n", indx);
    return NULL;
}



