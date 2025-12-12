// prototypes des fonctions utilitaires

#ifndef UTILS_H
#define UTILS_H

// fonctions pour la génération de tableaux de test (genration de données)
void generate_random_array(int arr[],int n);
void generate_sorted_array(int arr[], int n);
void generate_reverse_sorted_array(int arr[], int n);
void generate_partially_sorted_array(int arr[], int n, float percentage);

double measure_time(void (*sort_func)(int[], int), int arr[], int n);

// fonctions pour vérifier si un tableau est trié
int is_sorted(int arr[], int n);
void verify_sort(void (*sort_func)(int[], int), int arr[], int n);

// fonctions d'affichage 
void print_array(int arr[], int n);
void print_progress(int current, int total, const char *message);

#endif // UTILS_H
