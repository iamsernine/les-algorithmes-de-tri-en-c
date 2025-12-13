#include <stdio.h>
#include <stdlib.h>
#include "../../include/sort_algorithms.h"

void verify_sort(void (*sort_func)(int[], int), int arr[], int n) {
    int *arr_copy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }
    
    sort_func(arr_copy, n);
    
    if (is_sorted(arr_copy, n)) {
        printf("✓ Tri réussi\n");
    } else {
        printf("✗ Échec du tri\n");
    }
    
    free(arr_copy);
}

