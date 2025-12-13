#include "../../include/sort_algorithms.h"
#include <math.h>

// Helper function for HeapSort: heapify a subtree rooted with node i
// n is size of heap, offset is the starting index of the sub-array
static void heapify(int arr[], int n, int i, int offset) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[offset + left] > arr[offset + largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[offset + right] > arr[offset + largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[offset + i], &arr[offset + largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, offset);
    }
}

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
        int n_heap = high - low + 1; // Size of the current sub-array for heapsort

        // Build heap (rearrange array)
        for (int i = n_heap / 2 - 1; i >= 0; i--)
            heapify(arr, n_heap, i, low);

        // One by one extract an element from heap
        for (int i = n_heap - 1; i > 0; i--) {
            // Move current root to end
            swap(&arr[low], &arr[low + i]);

            // call max heapify on the reduced heap
            heapify(arr, i, 0, low);
        }
        return;
    }
    
    // Partition pour quick sort
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    
    int pi = i + 1;
    
    intro_sort_recursive(arr, low, pi - 1, depth_limit - 1);
    intro_sort_recursive(arr, pi + 1, high, depth_limit - 1);
}

void intro_sort_wrapper(int arr[], int n) {
    int depth_limit = 2 * (int)log2(n);
    intro_sort_recursive(arr, 0, n - 1, depth_limit);
}