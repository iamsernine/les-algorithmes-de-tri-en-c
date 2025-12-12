#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/sort_algorithms.h"

// struct pour stocker les resultats 

typedef  struct {
    char algorithm[50];
    int size;
    double time;
} Benchmarkresult;

// tableau pour les alorithmes a tester 
typedef struct {
    char name[50];
    void (*function)(int[], int);
    int max_test_size; // taille maximale de test pour l'algorithme
} Algorithm;


// prototypes des fonctions //

void run_comprehensive_benchmark();
void run_specific_test(int algorithm_index, int size);
void generate_size_file(const char *filename, int min, int max, int step);
void display_menu();


int main(){
    srand(time(NULL)); // initialiser le generateur de nombres aleatoires

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("lancement des benchmarks complets ......\n");
                run_comprehensive_benchmark();
                printf("benchmark complet termine avec succes , resultats dans data/results.csv\n");
                break;
            case 2:
                {
                printf("\n les algorithmes disponibles sont :\n");
                printf("1. bubble sort (max :50000)\n");
                printf("2. selection sort (max :50000)\n");
                printf("3. insertion sort (max :50000)\n");
                printf("4. shell sort (max :100000)\n");
                printf("5. heap sort (max :1000000)\n");
                printf("6. merge sort (max :1000000)\n");
                printf("7. quick sort (max :1000000)\n");
                printf("8. comb sort (max :1000000)\n");
                printf("9. counting sort (max :1000000)\n");

                int algo_choice, size;
                printf("entrez le numero de l'algorithme a tester : ");
                scanf("%d", &algo_choice);
                printf("entrez la taille du tableau a trier : ");
                scanf("%d", &size);

                if(algo_choice < 1 || algo_choice > 10){
                    printf("choix invalide !\n");
                    break;
                }

                run_specific_test(algo_choice - 1, size);
                break;
                }
            case 3:
                printf("genration du fichier de tailles ......\n");
                generate_size_file("data/sizes.txt", 1000, 1000000, 1000);
                printf("fichier de tailles genere avec succes dans data/sizes.txt\n");
                break;
            case 4:
                printf("genration des graphiques ......\n");
                system("cd plots && gnuplot plot.gp");
                printf("graphiques generes avec succes dans le dossier plots/\n");
                break;
            case 5:
                printf("quitting...\n");
                break;
            default:
                printf("choix invalide , veuillez reessayer.\n");
                
        }
    } while(choice != 5);

    return 0;
}

void display_menu(){
        printf("\n=== BENCHMARK ALGORITHMES DE TRI ===\n");
    printf("1. Lancer tous les benchmarks\n");
    printf("2. Tester un algorithme spécifique\n");
    printf("3. Générer le fichier de tailles\n");
    printf("4. Générer les graphiques\n");
    printf("5. Quitter\n");
    printf("Choix: ");
}

void run_comprehensive_benchmark(){
        // Définir les algorithmes à tester
    Algorithm algorithms[] = {
        {"Bubble", bubble_sort, 50000},
        {"Selection", selection_sort, 50000},
        {"Insertion", insertion_sort, 50000},
        {"Shell", shell_sort, 1000000},
        {"Heap", heap_sort, 1000000},
        {"Merge", merge_sort_wrapper, 1000000},
        {"Quick", quick_sort_wrapper, 1000000},
        {"Comb", comb_sort, 1000000},
        {"Counting", counting_sort, 1000000},
        {"Radix", radix_sort, 1000000}
    };

    int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    // creer data/ s'il nexiste pas (it's does exist :) ) [just to be sure and also check if the command works for ur system]
    system("mkdir -p data");

    // initialiser le fichier CSV
    write_csv_header("data/results.csv");

    // les parametres de benchmark
    int min_size = 1000;
    int max_size = 1000000;
    int step = 1000;
    int iterations = 3; // nbr d'itrations pour moyenne 

    printf(" debut ddes benchmarks sur %d algorithmes ......\n", num_algorithms);
    printf(" taille min : %d , taille max: %d , pas : %d \n", min_size, max_size, step);
    printf(" iterations par test : %d \n\n", iterations);

    // pour chaque taille 
    for(int size = min_size; size <= max_size  ; size += step){
        printf("test taille  : %d\n", size);
        fflush(stdout); // to force print to appear immediately

        // allouer et generer un tableau de test 
        int *reference_array  = malloc(size * sizeof(int));
        generate_random_array(reference_array, size);

        // pour chaque algorithm test 
        for (int i = 0 ; i <num_algorithms ;i++){
            // ne pas tester  sur les algorithmes lentes (si vous vouler tester quand meme , changez la condition)
            if(size > algorithms[i].max_test_size){
                printf(" taille grandes pour ce algorithme , saut du test %s\n", algorithms[i].name);
                continue;
            }

            double total_time = 0;

            // moyenne sur plusieurs iterations
            for(int iter=0 ;iter <iterations ;iter++){

                // copier le tableaur de refrence 
                int *test_array = malloc(size * sizeof(int));
                memcpy(test_array, reference_array, size * sizeof(int));

                // mesurer le temps
                clock_t start = clock();
                algorithms[i].function(test_array, size);
                clock_t end = clock();

                total_time += ((double)(end - start)) / CLOCKS_PER_SEC;

                // verifier lde tri 
                if(!is_sorted(test_array,size)){
                    printf("\n erreur : l'algorithme %s n'a pas trié correctement le tableau de taille %d\n", algorithms[i].name, size);
                }

                free(test_array);
            }
            double average_time = total_time / iterations;

            // ecrire les resultats dans le fichier csv
            write_csv_result("data/results.csv", algorithms[i].name, size, average_time);
        }
        free(reference_array);

        // afficher la progression
        if(size%10000 == 0){
            printf("progression %d/%d (%.1f%%)\n",size, max_size ,  (float)size/max_size *100);
        }
    }
    printf("\n benchmark termine !\n");
}

void run_specific_test(int algorithm_index, int size){
    // map des algorithmes
    void (*algorithms[])(int[], int) = {
        bubble_sort,
        selection_sort,
        insertion_sort,
        shell_sort,
        heap_sort,
        merge_sort_wrapper,
        quick_sort_wrapper,
        comb_sort,
        counting_sort,
        radix_sort
    };

    const char *names[] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Shell Sort",
        "Heap Sort",
        "Merge Sort",
        "Quick Sort",
        "Comb Sort",
        "Counting Sort",
        "Radix Sort"
    };

    if (algorithm_index < 0 || algorithm_index >= 10) {
        printf("Index d'algorithme invalide!\n");
        return;
    }

    printf("\ntest de %s sur tableau de taille %d ......\n", names[algorithm_index], size);

    // generer le tableau
    int *arr = malloc(size * sizeof(int));
    generate_random_array(arr, size);
    
    // copy
    int *arr_copy = malloc(size * sizeof(int));
    memcpy(arr_copy, arr, size * sizeof(int));
    
    //mesurer le temps
    clock_t start = clock();
    algorithms[algorithm_index](arr, size);
    clock_t end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    //verifier le tri
    if (is_sorted(arr, size)) {
        printf("tableau correctement trir\n");
    } else {
        printf("erreur :tableau non trie!\n");
    }
    
    printf("temps d'exécution: %.6f secondes\n", time_taken);
    
    free(arr);
    free(arr_copy);
}

void generate_size_file(const char *filename  , int min , int max ,int step){
    FILE *file = fopen(filename,"w");
    if(!file){
        print("erruer douvrir le fichier %s\n",filename );
        return;
    }

    for(int size = min  ; size <= max ; size+= step){
        fprintf(file,"%d\n",size);
    }

    fclose(file);
}