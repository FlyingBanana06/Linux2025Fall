// **Configuration**
#define ROUNDS 1
#define D_RDTSC 0
#define D_GETTIME 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// -----------------------------
// RDTSC
// -----------------------------
static inline uint64_t RDTSC() {
    unsigned int hi, lo;
    __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

// -----------------------------
// clock_gettime
// -----------------------------
double GETTIME() {
    struct timespec ts;
    double sec;
    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;
    return sec;
}

int main(int argc, char** argv)
{
    uint64_t measure_rdtsc = 0;
    double   measure_gettime = 0;
    uint64_t fib[50] = {0};

#if D_RDTSC
    uint64_t c1 = RDTSC();
#endif

#if D_GETTIME
    double t1 = GETTIME();
#endif

    for (int r = 0; r < ROUNDS; r++) {

        /* fix me → 實作 Fibonacci */
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i < 50; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }

#if D_RDTSC
    uint64_t cycle = RDTSC() - c1;
    measure_rdtsc = cycle;
#endif

#if D_GETTIME
    double time_s = GETTIME() - t1;
    measure_gettime += time_s;
#endif

    for(int i = 0; i < 50; i++) {
        printf("%lu ", fib[i]);
    }

    double cpu_rate = 2188.854;

    printf("\n");

#if D_RDTSC
    printf("%lu\n", measure_rdtsc);
    printf(" CPU time = %.10lf seconds |",
        (double)measure_rdtsc / ROUNDS / (cpu_rate * 1000000));
#endif

#if D_GETTIME
    printf(" GETTIME = %.10lf seconds | ",
        (double)measure_gettime / ROUNDS);
#endif

    printf("\n");
    return 0;
}

