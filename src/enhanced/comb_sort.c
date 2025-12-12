#include "../../include/sort_algorithms.h"

void comb_sort(int arr[], int n) {
    int gap = n;
    int swapped = 1;
    float shrink = 1.3;
    
    while (gap > 1 || swapped) {
        gap = (int)(gap / shrink);
        if (gap < 1) gap = 1;
        
        swapped = 0;
        
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
            }
        }
    }
}