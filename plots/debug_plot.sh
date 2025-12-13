#!/bin/bash

# Script de débogage pour gnuplot

echo "=== DÉBOGAGE GNUPLOT ==="
echo ""

# Vérifier si gnuplot est installé
if ! command -v gnuplot &> /dev/null; then
    echo "ERREUR: gnuplot n'est pas installé"
    echo "Installez avec: sudo apt-get install gnuplot"
    exit 1
fi

echo "1. Vérification de la version gnuplot:"
gnuplot --version

echo ""
echo "2. Vérification des fichiers de données:"
if [ -f "../data/results.csv" ]; then
    echo "Fichier results.csv trouvé"
    echo "Lignes: $(wc -l < ../data/results.csv)"
    echo "Premières lignes:"
    head -n 5 ../data/results.csv
else
    echo "ERREUR: ../data/results.csv non trouvé"
    echo "Exécutez d'abord un benchmark: make bench-quick"
    exit 1
fi

echo ""
echo "3. Test simple avec gnuplot:"
cat > test_plot.gp << 'EOF'
set terminal pngcairo size 800,600
set output 'test_plot.png'
set datafile separator comma
set title "Test de tracé"
set xlabel "Taille"
set ylabel "Temps"
set grid

# Tracer seulement bubble sort
plot '../data/results.csv' using 2:($1 eq "bubble" ? $3 : 1/0) title 'Bubble' with linespoints
EOF

gnuplot test_plot.gp

if [ -f "test_plot.png" ]; then
    echo "SUCCÈS: test_plot.png généré"
    rm test_plot.gp test_plot.png
else
    echo "ÉCHEC: Impossible de générer le graphique de test"
    exit 1
fi

echo ""
echo "4. Vérification du script principal:"
if [ -f "plot.gp" ]; then
    echo "Script plot.gp trouvé"
    
    # Tester chaque graphique
    for graph in all_algorithms nlogn_algorithms non_comparative theory_vs_practice; do
        echo -n "  Graphique $graph: "
        grep -q "set output.*$graph.png" plot.gp && echo "OK" || echo "NON TROUVÉ"
    done
else
    echo "ERREUR: plot.gp non trouvé"
    exit 1
fi

echo ""
echo "=== DÉBOGAGE TERMINÉ ==="
echo "Pour tester: make plot-simple"