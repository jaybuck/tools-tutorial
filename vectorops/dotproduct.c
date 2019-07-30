// Compute dot product of two vectors of doubles

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static size_t N = 10000000;

double dotproduct(double *v0, double *v1, size_t n) {
    double result = 0.0;
    size_t i;
    for(i = 0; i < n; ++i) {
        result += *v0++ * *v1++;
    }
    return result;
}

int main() {
    int rcode = 0;
    double *v0, *v1;
    size_t i;
    clock_t t0, t1;
    double tdelta;

    v0 = (double *) malloc(N * sizeof(double));
    v1 = (double *) malloc(N * sizeof(double));

    for(i = 0; i < N; ++i) {
        v0[i] = (double)(i);
        v1[i] = 1.0/((double)(i + 1)*(i + 1));
    }

    t0 = clock();
    double dotprod = dotproduct(v0, v1, N);
    t1 = clock();
    tdelta = (t1 - t0)/(double)CLOCKS_PER_SEC;

    printf("time: %lf\n", tdelta);
    printf("dotproduct: %lf\n", dotprod);

    free(v0);
    free(v1);
    return rcode;
}
