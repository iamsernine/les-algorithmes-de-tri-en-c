#include <stdio.h>
#include <string.h>

void write_csv_header(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return;
    }
    
    fprintf(file, "Algorithm,Size,Time(seconds)\n");
    fclose(file);
}

void write_csv_result(const char *filename, const char *algorithm, int size, double time) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return;
    }
    
    fprintf(file, "%s,%d,%.6f\n", algorithm, size, time);
    fclose(file);
}