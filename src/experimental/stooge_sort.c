#include "../../include/sort_algorithms.h"

static void stooge_sort_recursive(int arr[], int l, int h) {
    if (l >= h) return;
    
    if (arr[l] > arr[h]) {
        int temp = arr[l];
        arr[l] = arr[h];
        arr[h] = temp;
    }
    
    if (h - l + 1 > 2) {
        int t = (h - l + 1) / 3;
        
        stooge_sort_recursive(arr, l, h - t);
        stooge_sort_recursive(arr, l + t, h);
        stooge_sort_recursive(arr, l, h - t);
    }
}

void stooge_sort_wrapper(int arr[], int n) {
    stooge_sort_recursive(arr, 0, n - 1);
}