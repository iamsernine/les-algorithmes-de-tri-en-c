#include "../../include/sort_algorithms.h"



// Function to compare and swap elements based on direction
// dir = 1 for ascending, 0 for descending
static void compare_and_swap(int arr[], int i, int j, int dir) {
    if (dir == (arr[i] > arr[j])) {
        swap(&arr[i], &arr[j]);
    }
}

// Main function to initiate bitonic sort for arbitrary size
void bitonic_sort_wrapper(int arr[], int n) {
    if (n <= 1) {
        return;
    }

    int i, j, k;
    int dir = 1; // 1 for ascending sort

    for (k = 2; (k >> 1) < n; k <<= 1) {
        for (i = 0; i < n; i++) {
            int l = i ^ (k - 1);
            if (l > i && l < n) {
                compare_and_swap(arr, i, l, dir);
            }
        }
        for (j = k >> 1; j > 0; j >>= 1) {
            for (i = 0; i < n; i++) {
                int l = i ^ j;
                if (l > i && l < n) {
                    compare_and_swap(arr, i, l, dir);
                }
            }
        }
    }
}