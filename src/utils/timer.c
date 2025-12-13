#include <time.h>

double measure_time(void (*sort_func)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}