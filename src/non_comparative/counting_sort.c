#include "../../include/sort_algorithms.h"
#include <stdlib.h>

void counting_sort(int arr[], int n) {
    if (n == 0) return;
    
    // Trouver la valeur maximale
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    // Allouer le tableau de comptage
    int *count = (int*)calloc(max + 1, sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));
    
    // Compter les occurrences
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
    // Modifier count[i] pour qu'il contienne la position
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
    // Construire le tableau de sortie
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    // Copier dans le tableau original
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(count);
    free(output);
}