
set terminal pngcairo size 1200,800
set datafile separator comma
set key outside right top
set grid

set output 'simple_plot.png'
set title "Performances des Algorithmes de Tri"
set xlabel "Taille"
set ylabel "Temps (s)"

plot '../data/results_cleaned.csv' using 2:3:1 with points palette pt 7 ps 1 title ""
            