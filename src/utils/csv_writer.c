#include <stdio.h>
#include <string.h>
#include "utils.h"

void write_csv_header(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }
    fprintf(file, "Algorithm,Size,Time\n");
    fclose(file);
}

void write_csv_result(const char *filename, const char *algorithm, int size, double time) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }
    fprintf(file, "%s,%d,%.6f\n", algorithm, size, time);
    fclose(file);
}