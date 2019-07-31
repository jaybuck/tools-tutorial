// Compute dot product of two vectors of doubles in C++

#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <ctime>

using namespace std;

static size_t N = 10000000;

double dotproduct(const vector<double> &v0, const vector<double> &v1) {
    double result = 0.0;
    result = std::inner_product(v0.begin(), v0.end(), v1.begin(), 0.0);
    return result;
}

int main() {
    int rcode = 0;
    vector<double> v0(N);
    vector<double> v1(N);
    size_t i;
    clock_t t0, t1;
    double tdelta;

    for(i = 0; i < N; ++i) {
        v0[i] = (double)(i);
        v1[i] = 1.0/((double)(i + 1)*(i + 1));
    }

    t0 = clock();
    double dotprod = dotproduct(v0, v1);
    t1 = clock();
    tdelta = (t1 - t0)/(double)CLOCKS_PER_SEC;

    printf("time: %lf\n", tdelta);
    printf("dotproduct: %lf\n", dotprod);

    return rcode;
}
