#include <stdlib.h>
#include <time.h>

void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Valeurs entre 0 et 9999
    }
}

void generate_sorted_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generate_reverse_sorted_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void generate_partially_sorted_array(int arr[], int n, float percentage) {
    int sorted_part = (int)(n * percentage);
    
    // Partie triée
    for (int i = 0; i < sorted_part; i++) {
        arr[i] = i;
    }
    
    // Partie aléatoire
    for (int i = sorted_part; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}