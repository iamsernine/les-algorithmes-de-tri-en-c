#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <time.h>

// Supprimer le prototype de measure_time qui est déjà dans sort_algorithms.h
// Garder uniquement les fonctions de génération de données

// Génération de tableaux
void generate_random_array(int arr[], int n);
void generate_sorted_array(int arr[], int n);
void generate_reverse_sorted_array(int arr[], int n);
void generate_partially_sorted_array(int arr[], int n, float percentage);

// Fonctions de vérification
void verify_sort(void (*sort_func)(int[], int), int arr[], int n);

// Fonctions d'affichage
void print_progress(int current, int total, const char *message);

#endif // UTILS_H