#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

// ============================================
// Prototypes pour tous les algorithmes de tri
// ============================================

// Algorithmes classiques O(n²)
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void shell_sort(int arr[], int n);

// Algorithmes O(n log n)
void heap_sort(int arr[], int n);
void merge_sort_wrapper(int arr[], int n);
void quick_sort_wrapper(int arr[], int n);

// Algorithmes améliorés/hybrides
void comb_sort(int arr[], int n);
void cocktail_sort(int arr[], int n);
void cycle_sort(int arr[], int n);
void gnome_sort(int arr[], int n);
void tim_sort_wrapper(int arr[], int n);

// Algorithmes non comparatifs
void counting_sort(int arr[], int n);
void radix_sort(int arr[], int n);
void bucket_sort(int arr[], int n);
void pigeonhole_sort(int arr[], int n);

// Algorithmes expérimentaux
void bitonic_sort_wrapper(int arr[], int n);
void stooge_sort_wrapper(int arr[], int n);
void odd_even_sort(int arr[], int n);
void strand_sort_wrapper(int arr[], int n);
void intro_sort_wrapper(int arr[], int n);

// ============================================
// Fonctions utilitaires (helpers)
// ============================================

// Fonctions de base
void swap(int *a, int *b);
int get_max(int arr[], int n);
int get_min(int arr[], int n);
int is_sorted(int arr[], int n);
void print_array(int arr[], int n);

// Fonctions pour génération de données
void generate_random_array(int arr[], int n);
void generate_sorted_array(int arr[], int n);
void generate_reverse_sorted_array(int arr[], int n);
void generate_partially_sorted_array(int arr[], int n, float percentage);

// Fonctions de mesure de temps
double measure_time(void (*sort_func)(int[], int), int arr[], int n);

// Fonctions d'écriture de résultats
void write_csv_header(const char *filename);
void write_csv_result(const char *filename, const char *algorithm, int size, double time);

// ============================================
// Constantes
// ============================================

#define MIN_RUN 32
#define BUCKET_COUNT 10
#define RADIX_BASE 10

#endif // SORT_ALGORITHMS_H