#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "../include/sort_algorithms.h"

// ============================================
// Configuration des benchmarks
// ============================================

// Définition des algorithmes disponibles pour les benchmarks
typedef struct {
    const char* name;
    void (*function)(int[], int);
    int max_test_size;       // Taille maximale recommandée
    const char* category;    // Catégorie pour l'organisation
    const char* complexity;  // Complexité théorique
} Algorithm;

// Tableau complet des algorithmes implémentés
Algorithm all_algorithms[] = {
    // Algorithmes classiques O(n²)
    {"bubble", bubble_sort, 50000, "classical", "O(n²)"},
    {"selection", selection_sort, 50000, "classical", "O(n²)"},
    {"insertion", insertion_sort, 50000, "classical", "O(n²)"},
    {"shell", shell_sort, 1000000, "classical", "O(n log n) - O(n²)"},
    
    // Algorithmes O(n log n)
    {"heap", heap_sort, 1000000, "nlogn", "O(n log n)"},
    {"merge", merge_sort_wrapper, 1000000, "nlogn", "O(n log n)"},
    {"quick", quick_sort_wrapper, 1000000, "nlogn", "O(n log n)"},
    
    // Algorithmes améliorés/hybrides
    {"comb", comb_sort, 1000000, "enhanced", "O(n²)"},
    {"cocktail", cocktail_sort, 50000, "enhanced", "O(n²)"},
    {"cycle", cycle_sort, 50000, "enhanced", "O(n²)"},
    {"gnome", gnome_sort, 50000, "enhanced", "O(n²)"},
    {"tim", tim_sort_wrapper, 1000000, "enhanced", "O(n log n)"},
    
    // Algorithmes non comparatifs
    {"counting", counting_sort, 1000000, "non_comparative", "O(n+k)"},
    {"radix", radix_sort, 1000000, "non_comparative", "O(d*(n+b))"},
    {"bucket", bucket_sort, 1000000, "non_comparative", "O(n+k)"},
    {"pigeonhole", pigeonhole_sort, 1000000, "non_comparative", "O(n+k)"},
    
    // Algorithmes expérimentaux
    {"bitonic", bitonic_sort_wrapper, 100000, "experimental", "O(n log² n)"},
    {"stooge", stooge_sort_wrapper, 10000, "experimental", "O(n^2.71)"},
    {"oddeven", odd_even_sort, 50000, "experimental", "O(n²)"},
    {"strand", strand_sort_wrapper, 50000, "experimental", "O(n²)"},
    {"intro", intro_sort_wrapper, 1000000, "experimental", "O(n log n)"}
};

#define NUM_ALGORITHMS (sizeof(all_algorithms) / sizeof(all_algorithms[0]))

// ============================================
// Fonctions utilitaires
// ============================================

// Affiche l'usage du programme
void print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS]\n\n", program_name);
    printf("Options:\n");
    printf("  --help              Affiche ce message d'aide\n");
    printf("  --menu              Mode menu interactif (par défaut)\n");
    printf("  --bench-all         Exécute tous les benchmarks\n");
    printf("  --bench-algo NAME   Teste un algorithme spécifique\n");
    printf("  --size N            Taille du tableau (par défaut: 10000)\n");
    printf("  --min-size N        Taille minimale pour benchmark complet (défaut: 1000)\n");
    printf("  --max-size N        Taille maximale pour benchmark complet (défaut: 100000)\n");
    printf("  --step N            Pas entre les tailles (défaut: 1000)\n");
    printf("  --iterations N      Nombre d'itérations par test (défaut: 3)\n");
    printf("  --output FILE       Fichier de sortie CSV (défaut: data/results.csv)\n");
    printf("  --no-plot           Ne pas générer les graphiques\n");
    printf("\nAlgorithmes disponibles:\n");
    
    // Afficher par catégorie
    const char* categories[] = {"classical", "nlogn", "enhanced", "non_comparative", "experimental"};
    const char* category_names[] = {"Classiques (O(n²))", "O(n log n)", "Améliorés", "Non comparatifs", "Expérimentaux"};
    
    for (int cat = 0; cat < 5; cat++) {
        printf("\n  %s:\n", category_names[cat]);
        for (size_t i = 0; i < NUM_ALGORITHMS; i++) {
            if (strcmp(all_algorithms[i].category, categories[cat]) == 0) {
                printf("    %-15s (max: %7d, complexité: %s)\n",
                       all_algorithms[i].name,
                       all_algorithms[i].max_test_size,
                       all_algorithms[i].complexity);
            }
        }
    }
    printf("\nExemples:\n");
    printf("  %s --bench-all --min-size 1000 --max-size 50000\n", program_name);
    printf("  %s --bench-algo quick --size 100000\n", program_name);
    printf("  %s --bench-algo merge --size 50000 --iterations 5\n", program_name);
}

// Trouve un algorithme par son nom
Algorithm* find_algorithm(const char* name) {
    for (size_t i = 0; i < NUM_ALGORITHMS; i++) {
        if (strcmp(all_algorithms[i].name, name) == 0) {
            return &all_algorithms[i];
        }
    }
    return NULL;
}

// ============================================
// Fonctions de benchmarking
// ============================================

// Test d'un algorithme spécifique
void benchmark_single_algorithm(const char* algo_name, int size, int iterations, 
                                const char* output_file, int append) {
    Algorithm* algo = find_algorithm(algo_name);
    if (!algo) {
        printf("Erreur: Algorithme '%s' non trouvé\n", algo_name);
        return;
    }
    
    if (size > algo->max_test_size) {
        printf("Attention: Taille %d supérieure au maximum recommandé pour %s (%d)\n",
               size, algo_name, algo->max_test_size);
        printf("Voulez-vous continuer ? (o/n): ");
        char response = getchar();
        if (response != 'o' && response != 'O') {
            return;
        }
    }
    
    printf("\n=== Test de %s sur tableau de taille %d ===\n", algo_name, size);
    printf("Complexité théorique: %s\n", algo->complexity);
    printf("Catégorie: %s\n", algo->category);
    printf("Itérations: %d\n\n", iterations);
    
    // Initialiser le fichier CSV si nécessaire
    if (!append) {
        write_csv_header(output_file);
    }
    
    double total_time = 0;
    int success_count = 0;
    
    for (int iter = 0; iter < iterations; iter++) {
        // Générer le tableau
        int* arr = malloc(size * sizeof(int));
        generate_random_array(arr, size);
        
        // Faire une copie pour vérification
        int* arr_copy = malloc(size * sizeof(int));
        memcpy(arr_copy, arr, size * sizeof(int));
        
        // Mesurer le temps
        clock_t start = clock();
        algo->function(arr, size);
        clock_t end = clock();
        
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time += elapsed;
        
        // Vérifier le tri
        if (is_sorted(arr, size)) {
            success_count++;
            printf("  Itération %d: %.6f secondes ✓\n", iter + 1, elapsed);
        } else {
            printf("  Itération %d: %.6f secondes ✗ (tri échoué)\n", iter + 1, elapsed);
        }
        
        free(arr);
        free(arr_copy);
    }
    
    double avg_time = total_time / iterations;
    double success_rate = (double)success_count / iterations * 100;
    
    printf("\n=== Résultats ===\n");
    printf("Temps moyen: %.6f secondes\n", avg_time);
    printf("Taux de succès: %.1f%%\n", success_rate);
    printf("Temps total: %.6f secondes\n", total_time);
    
    // Écrire dans le fichier CSV
    write_csv_result(output_file, algo_name, size, avg_time);
    printf("Résultats écrits dans %s\n", output_file);
}

// Benchmark complet de tous les algorithmes
void benchmark_all_algorithms(int min_size, int max_size, int step, 
                             int iterations, const char* output_file) {
    printf("\n=== BENCHMARK COMPLET ===\n");
    printf("Tailles: de %d à %d (pas: %d)\n", min_size, max_size, step);
    printf("Itérations par test: %d\n", iterations);
    printf("Fichier de sortie: %s\n\n", output_file);
    
    // Initialiser le fichier CSV
    write_csv_header(output_file);
    
    // Créer le répertoire data si nécessaire
    system("mkdir -p data");
    
    // Variables de progression
    int total_tests = 0;
    for (int size = min_size; size <= max_size; size += step) {
        total_tests++;
    }
    total_tests *= NUM_ALGORITHMS;
    
    int current_test = 0;
    clock_t global_start = clock();
    
    // Pour chaque taille de tableau
    for (int size = min_size; size <= max_size; size += step) {
        printf("\n[Tailles: %d/%d] Test avec tableau de taille %d\n", 
               size, max_size, size);
        
        // Générer un tableau de référence pour cette taille
        int* reference_array = malloc(size * sizeof(int));
        generate_random_array(reference_array, size);
        
        // Tester chaque algorithme
        for (size_t i = 0; i < NUM_ALGORITHMS; i++) {
            current_test++;
            
            // Vérifier si l'algorithme peut être testé à cette taille
            if (size > all_algorithms[i].max_test_size) {
                printf("  %-15s: skip (taille > %d)\n", 
                       all_algorithms[i].name, all_algorithms[i].max_test_size);
                continue;
            }
            
            double total_time = 0;
            int valid = 1;
            
            // Exécuter plusieurs itérations
            for (int iter = 0; iter < iterations; iter++) {
                // Créer une copie du tableau de référence
                int* test_array = malloc(size * sizeof(int));
                memcpy(test_array, reference_array, size * sizeof(int));
                
                // Mesurer le temps
                clock_t start = clock();
                all_algorithms[i].function(test_array, size);
                clock_t end = clock();
                
                total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
                
                // Vérifier le tri
                if (!is_sorted(test_array, size)) {
                    valid = 0;
                    printf("  ERREUR: %s n'a pas trié correctement\n", 
                           all_algorithms[i].name);
                }
                
                free(test_array);
            }
            
            if (valid) {
                double avg_time = total_time / iterations;
                printf("  %-15s: %.6f s\n", all_algorithms[i].name, avg_time);
                write_csv_result(output_file, all_algorithms[i].name, size, avg_time);
            }
            
            // Afficher la progression
            float progress = (float)current_test / total_tests * 100;
            printf("  Progression: %.1f%%\r", progress);
            fflush(stdout);
        }
        
        free(reference_array);
    }
    
    clock_t global_end = clock();
    double total_elapsed = ((double)(global_end - global_start)) / CLOCKS_PER_SEC;
    
    printf("\n\n=== BENCHMARK TERMINÉ ===\n");
    printf("Temps total: %.2f secondes\n", total_elapsed);
    printf("Résultats dans: %s\n", output_file);
}

// ============================================
// Menu interactif
// ============================================

void interactive_menu() {
    int choice;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Tester un algorithme spécifique\n");
        printf("2. Lancer le benchmark complet\n");
        printf("3. Afficher la liste des algorithmes\n");
        printf("4. Générer les graphiques\n");
        printf("5. Quitter\n");
        printf("Choix: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }
        
        switch(choice) {
            case 1: {
                // Afficher les algorithmes par catégorie
                printf("\nChoisissez un algorithme:\n");
                
                int index = 1;
                const char* categories[] = {"classical", "nlogn", "enhanced", "non_comparative", "experimental"};
                const char* category_names[] = {"Classiques", "O(n log n)", "Améliorés", "Non comparatifs", "Expérimentaux"};
                
                for (int cat = 0; cat < 5; cat++) {
                    printf("\n  %s:\n", category_names[cat]);
                    for (size_t i = 0; i < NUM_ALGORITHMS; i++) {
                        if (strcmp(all_algorithms[i].category, categories[cat]) == 0) {
                            printf("    %2d. %-15s (max: %7d)\n", 
                                   index++, all_algorithms[i].name, 
                                   all_algorithms[i].max_test_size);
                        }
                    }
                }
                
                printf("\nNuméro de l'algorithme: ");
                int algo_num;
                scanf("%d", &algo_num);
                
                if (algo_num < 1 || algo_num > (int)NUM_ALGORITHMS) {
                    printf("Numéro invalide!\n");
                    break;
                }
                
                printf("Taille du tableau: ");
                int size;
                scanf("%d", &size);
                
                printf("Nombre d'itérations (défaut: 3): ");
                int iterations = 3;
                scanf("%d", &iterations);
                
                // Trouver l'algorithme par index
                int count = 0;
                Algorithm* selected = NULL;
                for (size_t i = 0; i < NUM_ALGORITHMS; i++) {
                    count++;
                    if (count == algo_num) {
                        selected = &all_algorithms[i];
                        break;
                    }
                }
                
                if (selected) {
                    benchmark_single_algorithm(selected->name, size, iterations, 
                                              "data/single_test.csv", 0);
                }
                break;
            }
                
            case 2: {
                int min_size, max_size, step, iterations;
                
                printf("\n=== Benchmark complet ===\n");
                printf("Taille minimale (défaut: 1000): ");
                scanf("%d", &min_size);
                
                printf("Taille maximale (défaut: 100000): ");
                scanf("%d", &max_size);
                
                printf("Pas entre les tailles (défaut: 1000): ");
                scanf("%d", &step);
                
                printf("Itérations par test (défaut: 3): ");
                scanf("%d", &iterations);
                
                benchmark_all_algorithms(min_size, max_size, step, iterations,
                                        "data/results.csv");
                
                printf("\nVoulez-vous générer les graphiques ? (o/n): ");
                char plot_choice = getchar();
                while (getchar() != '\n'); // Vider le buffer
                
                if (plot_choice == 'o' || plot_choice == 'O') {
                    system("cd plots && gnuplot plot.gp 2>/dev/null");
                    printf("Graphiques générés dans plots/\n");
                }
                break;
            }
                
            case 3:
                print_usage("sort_benchmark");
                break;
                
            case 4:
                printf("Génération des graphiques...\n");
                system("cd plots && gnuplot plot.gp 2>/dev/null");
                printf("Graphiques générés dans plots/\n");
                break;
                
            case 5:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix invalide!\n");
        }
    } while (choice != 5);
}

// ============================================
// Fonction principale avec arguments
// ============================================

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    // Créer les répertoires nécessaires
    system("mkdir -p data plots");
    
    // Valeurs par défaut
    int bench_all = 0;
    int bench_algo = 0;
    char* algo_name = NULL;
    int size = 10000;
    int min_size = 1000;
    int max_size = 100000;
    int step = 1000;
    int iterations = 3;
    int generate_plot = 1;
    char* output_file = "data/results.csv";
    
    // Analyser les arguments de ligne de commande
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                print_usage(argv[0]);
                return 0;
            }
            else if (strcmp(argv[i], "--menu") == 0) {
                interactive_menu();
                return 0;
            }
            else if (strcmp(argv[i], "--bench-all") == 0) {
                bench_all = 1;
            }
            else if (strcmp(argv[i], "--bench-algo") == 0 && i + 1 < argc) {
                bench_algo = 1;
                algo_name = argv[++i];
            }
            else if (strcmp(argv[i], "--size") == 0 && i + 1 < argc) {
                size = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--min-size") == 0 && i + 1 < argc) {
                min_size = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--max-size") == 0 && i + 1 < argc) {
                max_size = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--step") == 0 && i + 1 < argc) {
                step = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
                iterations = atoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
                output_file = argv[++i];
            }
            else if (strcmp(argv[i], "--no-plot") == 0) {
                generate_plot = 0;
            }
            else {
                printf("Argument inconnu: %s\n", argv[i]);
                print_usage(argv[0]);
                return 1;
            }
        }
        
        // Exécuter selon les arguments
        if (bench_all) {
            benchmark_all_algorithms(min_size, max_size, step, iterations, output_file);
            if (generate_plot) {
                system("cd plots && gnuplot plot.gp 2>/dev/null");
                printf("Graphiques générés dans plots/\n");
            }
        }
        else if (bench_algo && algo_name) {
            benchmark_single_algorithm(algo_name, size, iterations, output_file, 0);
        }
        else {
            // Mode interactif par défaut
            interactive_menu();
        }
    }
    else {
        // Pas d'arguments: mode interactif
        interactive_menu();
    }
    
    return 0;
}