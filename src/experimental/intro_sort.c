#include "../../include/sort_algorithms.h"
#include <math.h>

static void intro_sort_recursive(int arr[], int low, int high, int depth_limit) {
    int size = high - low + 1;
    
    if (size < 16) {
        // Utiliser insertion sort pour les petits tableaux
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    
    if (depth_limit == 0) {
        // Utiliser heap sort si la profondeur est dépassée
        // Construction du tas max
        for (int i = low + size / 2 - 1; i >= low; i--) {
            int largest = i;
            int left = 2 * (i - low) + 1 + low;
            int right = 2 * (i - low) + 2 + low;
            
            if (left <= high && arr[left] > arr[largest])
                largest = left;
            
            if (right <= high && arr[right] > arr[largest])
                largest = right;
            
            if (largest != i) {
                int temp = arr[i];
                arr[i] = arr[largest];
                arr[largest] = temp;
            }
        }
        
        // Extraction des éléments
        for (int i = high; i > low; i--) {
            int temp = arr[low];
            arr[low] = arr[i];
            arr[i] = temp;
        }
        return;
    }
    
    // Partition pour quick sort
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    int pi = i + 1;
    
    intro_sort_recursive(arr, low, pi - 1, depth_limit - 1);
    intro_sort_recursive(arr, pi + 1, high, depth_limit - 1);
}

void intro_sort_wrapper(int arr[], int n) {
    int depth_limit = 2 * (int)log2(n);
    intro_sort_recursive(arr, 0, n - 1, depth_limit);
}