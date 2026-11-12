

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char name[32];
    double log2_value;  
} Func;

double log2_n_log2n(double n)   { return log2(n) * log2(n); }         
double log2_twelve_sqrt(double n){ return log2(12.0) + 0.5 * log2(n); }   
double log2_inv_n(double n)     { return -log2(n); }     
double log2_n_pow_log2n(double n){ return log2(n) * log2(n); }  
double log2_quad_full(double n) { return log2(100.0) + 2.0 * log2(n); }
double log2_n051(double n)      { return 0.51 * log2(n); }                 
double log2_quad_minus(double n){ return 2.0 * log2(n); }
double log2_fifty_sqrt(double n){ return log2(50.0) + 0.5 * log2(n); }     
double log2_cube(double n)      { return log2(2.0) + 3.0 * log2(n); }     
double log2_three_pow_n(double n){ return n * log2(3.0); }             
double log2_two_pow_32n(double n){ return 32.0 * n; }           
double log2_log2n(double n)     { return log2(log2(n)); }             

int cmp(const void *a, const void *b) {
    double da = ((Func *)a)->log2_value;
    double db = ((Func *)b)->log2_value;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

int main(void) {
   
    double n = 1.0e200;

    Func funcs[] = {
        {"n log2 n",       log2(n) + log2(log2(n))},
        {"12*sqrt(n)",     log2_twelve_sqrt(n)},
        {"1/n",            log2_inv_n(n)},
        {"n^(log2 n)",     log2_n_pow_log2n(n)},
        {"100n^2 + 6n",    log2_quad_full(n)},
        {"n^0.51",         log2_n051(n)},
        {"n^2 - 324",      log2_quad_minus(n)},
        {"50*n^0.5",       log2_fifty_sqrt(n)},
        {"2n^3",           log2_cube(n)},
        {"3^n",            log2_three_pow_n(n)},
        {"2^(32n)",        log2_two_pow_32n(n)},
        {"log2 n",         log2_log2n(n)}
    };

    int count = sizeof(funcs) / sizeof(funcs[0]);
    qsort(funcs, count, sizeof(Func), cmp);

    printf("Increasing order of growth (evaluated at n = %.3e):\n\n", n);
    for (int i = 0; i < count; i++) {
        printf("%2d. %-14s   (log2 f(n) = %.4f)\n", i + 1, funcs[i].name, funcs[i].log2_value);
    }
    return 0;
}
