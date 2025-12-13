#include "../../include/sort_algorithms.h"
#include <stdio.h>
int get_max(int arr[], int n) {
    if (n <= 0) return -1;
    
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int get_min(int arr[], int n) {
    if (n <= 0) return -1;
    
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n && i < 20; i++) {
        printf("%d", arr[i]);
        if (i < n - 1 && i < 19) printf(", ");
    }
    if (n > 20) printf(", ...");
    printf("]\n");
}