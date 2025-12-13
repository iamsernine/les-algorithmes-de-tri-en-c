#!/usr/bin/env python3
"""
Script de prétraitement des données CSV pour gnuplot
"""

import csv
import sys
import os

def clean_csv(input_file, output_file):
    """Nettoie le fichier CSV et le formate pour gnuplot"""
    if not os.path.exists(input_file):
        print(f"Fichier {input_file} non trouvé")
        return False
    
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        reader = csv.reader(f_in)
        writer = csv.writer(f_out)
        
        # Écrire l'en-tête
        writer.writerow(['Algorithm', 'Size', 'Time'])
        
        # Traiter les lignes
        header_skipped = False
        for row in reader:
            if not header_skipped:
                header_skipped = True
                continue
            
            if len(row) >= 3:
                # Nettoyer les noms d'algorithmes
                algo = row[0].strip().lower()
                size = row[1].strip()
                time = row[2].strip()
                
                # Convertir en float pour vérifier
                try:
                    float_time = float(time)
                    if float_time > 0:  # Ignorer les temps négatifs ou nuls
                        writer.writerow([algo, size, time])
                except ValueError:
                    continue
    
    print(f"Fichier nettoyé: {output_file}")
    return True

def create_category_files(input_file, categories):
    """Crée des fichiers CSV par catégorie"""
    if not os.path.exists(input_file):
        return
    
    data_by_category = {category: [] for category in categories}
    
    with open(input_file, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            algo = row['Algorithm'].lower()
            
            # Déterminer la catégorie
            category = 'other'
            if algo in ['bubble', 'selection', 'insertion']:
                category = 'quadratic'
            elif algo in ['heap', 'merge', 'quick', 'shell', 'tim', 'comb']:
                category = 'nlogn'
            elif algo in ['counting', 'radix', 'bucket', 'pigeonhole']:
                category = 'non_comparative'
            
            if category in data_by_category:
                data_by_category[category].append(row)
    
    # Écrire les fichiers par catégorie
    for category, rows in data_by_category.items():
        if rows:
            output_file = f"../data/{category}_data.csv"
            with open(output_file, 'w') as f:
                writer = csv.DictWriter(f, fieldnames=['Algorithm', 'Size', 'Time'])
                writer.writeheader()
                writer.writerows(rows)
            print(f"Fichier créé: {output_file}")

if __name__ == "__main__":
    input_csv = "../data/results.csv"
    cleaned_csv = "../data/results_cleaned.csv"
    
    if clean_csv(input_csv, cleaned_csv):
        categories = ['quadratic', 'nlogn', 'non_comparative']
        create_category_files(cleaned_csv, categories)
        
        # Créer un script gnuplot simplifié
        with open("plot_simple.gp", "w") as f:
            f.write("""
set terminal pngcairo size 1200,800
set datafile separator comma
set key outside right top
set grid

set output 'simple_plot.png'
set title "Performances des Algorithmes de Tri"
set xlabel "Taille"
set ylabel "Temps (s)"

plot '../data/results_cleaned.csv' using 2:3:1 with points palette pt 7 ps 1 title ""
            """)
        print("Script gnuplot simple généré: plot_simple.gp")