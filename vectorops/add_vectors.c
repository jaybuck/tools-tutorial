// Add two vectors of doubles

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static size_t N = 10000000;

void add_vectors(double *v0, double *v1, double *v2, size_t n) {
    size_t i;
    for(i = 0; i < n; ++i) {
        // v2[i] = v0[i] + v1[i];
        // This is just a bit faster:
        *v2++ = *v0++ + *v1++;
    }
}

int main() {
    int rcode = 0;
    double *v0, *v1, *v2;
    size_t i;
    clock_t t0, t1;
    double tdelta;

    v0 = (double *) malloc(N * sizeof(double));
    v1 = (double *) malloc(N * sizeof(double));
    v2 = (double *) malloc(N * sizeof(double));

    for(i = 0; i < N; ++i) {
        v0[i] = (double)(i + 1);
        v1[i] = 1.0/(double)(i + 1);
    }

    t0 = clock();
    add_vectors(v0, v1, v2, N);
    t1 = clock();
    tdelta = (t1 - t0)/(double)CLOCKS_PER_SEC;

    printf("time: %lf\n", tdelta);

    free(v0);
    free(v1);
    free(v2);
    return rcode;
}
