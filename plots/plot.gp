#!/usr/bin/gnuplot

# Configuration
set terminal pngcairo size 1600,1000 enhanced font 'Verdana,14'
set datafile separator comma
set key outside right top
set grid

# Styles de ligne
set style line 1 lc rgb '#FF0000' lt 1 lw 3 pt 7 ps 1.0  # Rouge - bubble
set style line 2 lc rgb '#00FF00' lt 1 lw 3 pt 7 ps 1.0  # Vert - selection
set style line 3 lc rgb '#0000FF' lt 1 lw 3 pt 7 ps 1.0  # Bleu - insertion
set style line 4 lc rgb '#FFA500' lt 1 lw 3 pt 7 ps 1.0  # Orange - shell
set style line 5 lc rgb '#800080' lt 1 lw 3 pt 7 ps 1.0  # Violet - heap
set style line 6 lc rgb '#00FFFF' lt 1 lw 3 pt 7 ps 1.0  # Cyan - merge
set style line 7 lc rgb '#FF00FF' lt 1 lw 3 pt 7 ps 1.0  # Magenta - quick
set style line 8 lc rgb '#A52A2A' lt 1 lw 3 pt 7 ps 1.0  # Marron - comb
set style line 9 lc rgb '#008080' lt 1 lw 3 pt 7 ps 1.0  # Teal - counting
set style line 10 lc rgb '#FFD700' lt 1 lw 3 pt 7 ps 1.0 # Or - radix
set style line 11 lc rgb '#FF1493' lt 1 lw 3 pt 7 ps 1.0 # Pink - bucket
set style line 12 lc rgb '#8B4513' lt 1 lw 3 pt 7 ps 1.0 # Brown - pigeonhole

# ====================================================================
# Fonction pour vérifier si le fichier existe et a des données
# ====================================================================
file_exists_and_not_empty(filename) = system("[ -s '".filename."' ] && echo 1 || echo 0") + 0

# ====================================================================
# Graphique 1: Tous les algorithmes (échelle linéaire)
# ====================================================================
set output 'all_algorithms.png'
set title "Comparaison de Tous les Algorithmes de Tri - Échelle Linéaire"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Temps d'Exécution (secondes)"
set xrange [1000:50000]
set yrange [0:*]

if (file_exists_and_not_empty("../data/results.csv")) {
    # Créer un tableau temporaire avec les données filtrées
    stats "../data/results.csv" using 2:3 nooutput
    
    plot for [i=0:11] \
        '../data/results.csv' using 2:($1 eq word("bubble,selection,insertion,shell,heap,merge,quick,comb,counting,radix,bucket,pigeonhole", i+1) ? $3 : 1/0) \
        title word("Bubble,Selection,Insertion,Shell,Heap,Merge,Quick,Comb,Counting,Radix,Bucket,Pigeonhole", i+1) \
        with linespoints ls i+1
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 2: Algorithmes O(n log n) seulement
# ====================================================================
set output 'nlogn_algorithms.png'
set title "Algorithmes O(n log n) - Grandes Tailles"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Temps d'Exécution (secondes)"
set xrange [1000:*]
set yrange [0:*]
set logscale x
# Pas de logscale y pour voir les différences clairement

if (file_exists_and_not_empty("../data/results.csv")) {
    plot '../data/results.csv' using 2:($1 eq "heap" ? $3 : 1/0) title 'Heap Sort' with linespoints ls 5, \
         '' using 2:($1 eq "merge" ? $3 : 1/0) title 'Merge Sort' with linespoints ls 6, \
         '' using 2:($1 eq "quick" ? $3 : 1/0) title 'Quick Sort' with linespoints ls 7, \
         '' using 2:($1 eq "shell" ? $3 : 1/0) title 'Shell Sort' with linespoints ls 4, \
         '' using 2:($1 eq "tim" ? $3 : 1/0) title 'Tim Sort' with linespoints ls 8, \
         '' using 2:($1 eq "comb" ? $3 : 1/0) title 'Comb Sort' with linespoints ls 9
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 3: Algorithmes non comparatifs
# ====================================================================
set output 'non_comparative.png'
set title "Algorithmes Non Comparatifs"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Temps d'Exécution (secondes)"
unset logscale
set xrange [1000:*]
set yrange [0:*]

if (file_exists_and_not_empty("../data/results.csv")) {
    plot '../data/results.csv' using 2:($1 eq "counting" ? $3 : 1/0) title 'Counting Sort' with linespoints ls 9, \
         '' using 2:($1 eq "radix" ? $3 : 1/0) title 'Radix Sort' with linespoints ls 10, \
         '' using 2:($1 eq "bucket" ? $3 : 1/0) title 'Bucket Sort' with linespoints ls 11, \
         '' using 2:($1 eq "pigeonhole" ? $3 : 1/0) title 'Pigeonhole Sort' with linespoints ls 12
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 4: Comparaison théorique vs pratique (log-log)
# ====================================================================
set output 'theory_vs_practice.png'
set title "Comparaison Complexité Théorique vs Temps Réel (Échelle Log-Log)"
set xlabel "Taille du Tableau (log)"
set ylabel "Temps d'Exécution (log)"
set logscale xy
set xrange [1000:1000000]
set yrange [0.00001:100]

# Courbes théoriques (normalisées pour l'affichage)
n2(x) = 5e-10 * x**2
nlogn(x) = 1e-8 * x * log(x)/log(2)
n(x) = 1e-7 * x

if (file_exists_and_not_empty("../data/results.csv")) {
    plot '../data/results.csv' using 2:($1 eq "bubble" ? $3 : 1/0) title 'Bubble (O(n²))' with linespoints ls 1, \
         '../data/results.csv' using 2:($1 eq "selection" ? $3 : 1/0) title 'Selection (O(n²))' with linespoints ls 2, \
         '../data/results.csv' using 2:($1 eq "quick" ? $3 : 1/0) title 'Quick (O(n log n))' with linespoints ls 7, \
         '../data/results.csv' using 2:($1 eq "counting" ? $3 : 1/0) title 'Counting (O(n))' with linespoints ls 9, \
         n2(x) title 'Théorique O(n²)' with lines lc rgb '#888888' dt 2 lw 2, \
         nlogn(x) title 'Théorique O(n log n)' with lines lc rgb '#888888' dt 3 lw 2, \
         n(x) title 'Théorique O(n)' with lines lc rgb '#888888' dt 4 lw 2
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 5: Algorithmes O(n²) seulement
# ====================================================================
set output 'quadratic_algorithms.png'
set title "Algorithmes O(n²) - Petites Tailles"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Temps d'Exécution (secondes)"
unset logscale
set xrange [1000:50000]
set yrange [0:*]

if (file_exists_and_not_empty("../data/results.csv")) {
    plot '../data/results.csv' using 2:($1 eq "bubble" ? $3 : 1/0) title 'Bubble Sort' with linespoints ls 1, \
         '' using 2:($1 eq "selection" ? $3 : 1/0) title 'Selection Sort' with linespoints ls 2, \
         '' using 2:($1 eq "insertion" ? $3 : 1/0) title 'Insertion Sort' with linespoints ls 3
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 6: Performance relative (Quick Sort = 1)
# ====================================================================
set output 'performance_ratio.png'
set title "Performance Relative (Quick Sort = Référence)"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Ratio de Temps (vs Quick Sort)"
unset logscale
set xrange [1000:50000]
set yrange [0:*]

# Ce graphique nécessite un prétraitement des données
if (file_exists_and_not_empty("../data/results.csv")) {
    # Créer un fichier temporaire avec les ratios
    system("awk -F, 'BEGIN{OFS=\",\"} NR==1{print \"Algorithm\",\"Size\",\"Ratio\"} NR>1{data[$1][$2]=$3} END{for(a in data) for(s in data[a]) if(data[\"quick\"][s] > 0) print a,s,data[a][s]/data[\"quick\"][s]}' ../data/results.csv > ../data/ratios.csv")
    
    if (file_exists_and_not_empty("../data/ratios.csv")) {
        plot '../data/ratios.csv' using 2:($1 eq "bubble" ? $3 : 1/0) title 'Bubble/Quick' with linespoints ls 1, \
             '' using 2:($1 eq "selection" ? $3 : 1/0) title 'Selection/Quick' with linespoints ls 2, \
             '' using 2:($1 eq "insertion" ? $3 : 1/0) title 'Insertion/Quick' with linespoints ls 3, \
             '' using 2:($1 eq "heap" ? $3 : 1/0) title 'Heap/Quick' with linespoints ls 5, \
             '' using 2:($1 eq "merge" ? $3 : 1/0) title 'Merge/Quick' with linespoints ls 6
    } else {
        set label 1 "Impossible de calculer les ratios" at graph 0.5,0.5 center
        plot 1/0 notitle
    }
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

# ====================================================================
# Graphique 7: Vue d'ensemble sur échelle semi-log
# ====================================================================
set output 'overview_semilog.png'
set title "Vue d'Ensemble des Performances (Échelle Semi-Log)"
set xlabel "Taille du Tableau (éléments)"
set ylabel "Temps d'Exécution (secondes, log)"
set logscale y
set xrange [1000:*]
set yrange [0.00001:100]

if (file_exists_and_not_empty("../data/results.csv")) {
    plot for [i=0:6] \
        '../data/results.csv' using 2:($1 eq word("bubble,selection,insertion,heap,merge,quick,counting", i+1) ? $3 : 1/0) \
        title word("Bubble,Selection,Insertion,Heap,Merge,Quick,Counting", i+1) \
        with linespoints ls i+1
} else {
    set label 1 "Aucune donnée disponible" at graph 0.5,0.5 center
    plot 1/0 notitle
}

print "Graphiques générés avec succès!"