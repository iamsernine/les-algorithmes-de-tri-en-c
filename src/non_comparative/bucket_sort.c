#include "../../include/sort_algorithms.h"
#include <stdlib.h>

typedef struct {
    int *values;
    int count;
} Bucket;

// Fonction interne pour bucket sort
static void bucket_find_min_max(int arr[], int n, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void bucket_sort(int arr[], int n) {
    if (n <= 0) return;
    
    int min, max;
    bucket_find_min_max(arr, n, &min, &max);
    
    Bucket *buckets = (Bucket*)malloc(BUCKET_COUNT * sizeof(Bucket));
    
    for (int i = 0; i < BUCKET_COUNT; i++) {
        buckets[i].values = (int*)malloc(n * sizeof(int));
        buckets[i].count = 0;
    }
    
    float range = (float)(max - min + 1) / BUCKET_COUNT;
    
    for (int i = 0; i < n; i++) {
        int bucket_index = (int)((arr[i] - min) / range);
        if (bucket_index >= BUCKET_COUNT) bucket_index = BUCKET_COUNT - 1;
        
        buckets[bucket_index].values[buckets[bucket_index].count] = arr[i];
        buckets[bucket_index].count++;
    }
    
    int index = 0;
    for (int i = 0; i < BUCKET_COUNT; i++) {
        if (buckets[i].count > 0) {
            // Tri par insertion sur le bucket
            for (int j = 1; j < buckets[i].count; j++) {
                int key = buckets[i].values[j];
                int k = j - 1;
                
                while (k >= 0 && buckets[i].values[k] > key) {
                    buckets[i].values[k + 1] = buckets[i].values[k];
                    k--;
                }
                buckets[i].values[k + 1] = key;
            }
            
            for (int j = 0; j < buckets[i].count; j++) {
                arr[index++] = buckets[i].values[j];
            }
        }
        free(buckets[i].values);
    }
    
    free(buckets);
}