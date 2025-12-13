#include "../../include/sort_algorithms.h"
#include <stdlib.h>

// Fonction interne pour pigeonhole sort
static void pigeonhole_find_min_max(int arr[], int n, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void pigeonhole_sort(int arr[], int n) {
    if (n <= 0) return;
    
    int min, max;
    pigeonhole_find_min_max(arr, n, &min, &max);
    
    int range = max - min + 1;
    int *holes = (int*)calloc(range, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        holes[arr[i] - min]++;
    }
    
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (holes[i] > 0) {
            arr[index++] = i + min;
            holes[i]--;
        }
    }
    
    free(holes);
}