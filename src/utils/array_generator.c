#include <stdlib.h>
#include <time.h>
#include "utils.h"

void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; // valeurs entre 0 et 99999
    }
}

void generate_sorted_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generate_reverse_sorted_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i; // TODO : look if it's working with just -i or n - i - 1
    }
}

void generate_partially_sorted_array(int arr[], int n, float percentage) {
    int sorted_part = (int)(n * percentage);

    // partie triee
    for (int i = 0; i < sorted_part; i++) {
        arr[i] = i;
    }

    // partie aleatoire
    for (int i = sorted_part; i < n; i++) {
        arr[i] = rand() % 100000;   
    }
}