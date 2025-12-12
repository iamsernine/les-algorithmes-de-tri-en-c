// Prototypes pour tous les algorithmes de tri

#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

// les alogirthmes de tri classiques O(n^2)
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void shell_sort(int arr[], int n);

// les algorithmes de tri O(n log n)
void heap_sort(int arr[], int n);
void merge_sort_wrapper(int arr[], int n);
void quick_sort_wrapper(int arr[], int n);

// les algorithmes de tri amiliorés et hybrides
void comb_sort(int arr[], int n);
void cocktail_sort(int arr[], int n);
void cycle_sort(int arr[], int n);
void gnome_sort(int arr[], int n);
void tim_sort_wrapper(int arr[], int n);

// les algorithmes de tri non-comparatifs
void counting_sort(int arr[], int n);
void radix_sort(int arr[], int n);
void bucket_sort(int arr[], int n);
void pigeonhole_sort(int arr[], int n);

// les algorithmes de tri expérimentaux 
void bitonic_sort_wrapper(int arr[], int n);
void stooge_sort_wrapper(int arr[], int n);
void odd_even_sort(int arr[], int n);
void strand_sort_wrapper(int arr[], int n);
void intro_sort_wrapper(int arr[], int n);

// fonctions utilitaires pour les algorithmes de tri
void swap(int *a, int *b);
int get_max(int arr[], int n); 
int get_min(int arr[], int n);
int is_sorted(int arr[], int n);
void print_array(int arr[], int n);

// fonctions pour la génération de tableaux de test (genration de données)
void generate_random_array(int arr[],int n);
void generate_sorted_array(int arr[], int n);
void generate_reverse_sorted_array(int arr[], int n);
void generate_partially_sorted_array(int arr[], int n, float percentage);

// fonctions pour mesurer le temps d'exécution des algorithmes de tri
double measure_time(void (*sort_func)(int[], int), int arr[], int n);
void benchmark_all_algorithms(int min_size, int max_size, int step, int iterations);

// fonctions d'ecriture de resultats
void write_csv_header(const char *filename);
void write_csv_result(const char *filename, const char *algorithm, int size, double time);

// constantes pour les algorithmes de tri
#define MIN_RUN 32 // pour Tim Sort
#define BUCKET_COUNT 10 // pour Bucket Sort
#define RADIX_BASE 10 // pour Radix Sort

#endif // SORT_ALGORITHMS_H