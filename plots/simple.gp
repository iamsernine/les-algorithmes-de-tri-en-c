set terminal png size 1200,800
set output 'plots/simple.png'
set datafile separator comma
set title 'Performances des Algorithmes'
set xlabel 'Taille'
set ylabel 'Temps (s)'
set grid
plot 'data/results_cleaned.csv' using 2:3:1 with points palette pt 7 ps 1 title ''
