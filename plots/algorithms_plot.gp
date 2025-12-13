set terminal pngcairo size 1024,768 enhanced font 'Verdana,10'
set output 'plots/algorithms_performance.png'

set title "Performance des algorithmes de tri"
set xlabel "Taille du tableau"
set ylabel "Temps d'execution (s)"
set grid
set logscale y
set format y "10^{%L}"


set datafile separator ","

set key outside

plot "< grep '^bubble,' data/results_cleaned.csv" using 2:3 with lines title "Bulle", \
     "< grep '^selection,' data/results_cleaned.csv" using 2:3 with lines title "Selection", \
     "< grep '^insertion,' data/results_cleaned.csv" using 2:3 with lines title "Insertion", \
     "< grep '^shell,' data/results_cleaned.csv" using 2:3 with lines title "Shell", \
     "< grep '^heap,' data/results_cleaned.csv" using 2:3 with lines title "Tas", \
     "< grep '^merge,' data/results_cleaned.csv" using 2:3 with lines title "Fusion", \
     "< grep '^quick,' data/results_cleaned.csv" using 2:3 with lines title "Rapide", \
     "< grep '^comb,' data/results_cleaned.csv" using 2:3 with lines title "Comb", \
     "< grep '^cocktail,' data/results_cleaned.csv" using 2:3 with lines title "Cocktail", \
     "< grep '^cycle,' data/results_cleaned.csv" using 2:3 with lines title "Cycle", \
     "< grep '^gnome,' data/results_cleaned.csv" using 2:3 with lines title "Gnome", \
     "< grep '^tim,' data/results_cleaned.csv" using 2:3 with lines title "Tim", \
     "< grep '^counting,' data/results_cleaned.csv" using 2:3 with lines title "Comptage", \
     "< grep '^radix,' data/results_cleaned.csv" using 2:3 with lines title "Radix", \
     "< grep '^bucket,' data/results_cleaned.csv" using 2:3 with lines title "Seau", \
     "< grep '^pigeonhole,' data/results_cleaned.csv" using 2:3 with lines title "Tiroirs", \
     "< grep '^bitonic,' data/results_cleaned.csv" using 2:3 with lines title "Bitonique", \
     "< grep '^stooge,' data/results_cleaned.csv" using 2:3 with lines title "Stooge", \
     "< grep '^oddeven,' data/results_cleaned.csv" using 2:3 with lines title "Pair-Impair", \
     "< grep '^strand,' data/results_cleaned.csv" using 2:3 with lines title "Strand", \
     "< grep '^intro,' data/results_cleaned.csv" using 2:3 with lines title "Intro"
