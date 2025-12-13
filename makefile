# Compilateur et options
CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I./include
LDFLAGS = -lm

# Valeurs par défaut pour les benchmarks
MIN_SIZE = 1000
MAX_SIZE = 10000
STEP = 1000
ITERATIONS = 2
TIMEOUT_BENCH = 1800

# Répertoires
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
DATA_DIR = data
PLOTS_DIR = plots
DOCS_DIR = docs

# Exécutable principal
TARGET = sort_benchmark

# Sources
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Cible par défaut
all: directories $(BIN_DIR)/$(TARGET)

# Création des répertoires
directories:
	@mkdir -p $(BUILD_DIR)/utils
	@mkdir -p $(BUILD_DIR)/classical
	@mkdir -p $(BUILD_DIR)/nlogn
	@mkdir -p $(BUILD_DIR)/enhanced
	@mkdir -p $(BUILD_DIR)/non_comparative
	@mkdir -p $(BUILD_DIR)/experimental
	@mkdir -p $(BUILD_DIR)/helpers
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DATA_DIR)
	@mkdir -p $(PLOTS_DIR)
	@mkdir -p $(DOCS_DIR)

# Compilation de l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Règle générique pour les fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)/$(TARGET)

clean-all: clean
	rm -rf $(DATA_DIR)/*.csv $(DATA_DIR)/*.txt $(PLOTS_DIR)/*.png

# ============================================
# COMMANDES DE BENCHMARK
# ============================================

# Benchmark complet standard (1000-50000)
bench-full: all
	@echo "=== Benchmark complet ($(MIN_SIZE)-$(MAX_SIZE)) ==="
	@timeout $(TIMEOUT_BENCH) ./$(BIN_DIR)/$(TARGET) --bench-all --min-size $(MIN_SIZE) --max-size $(MAX_SIZE) --step $(STEP) --iterations $(ITERATIONS) --output $(DATA_DIR)/results.csv || echo "Benchmark terminé (peut-être timeout)"

# Benchmark rapide (juste quelques tailles)
bench-quick: all
	@echo "=== Benchmark rapide ==="
	@./$(BIN_DIR)/$(TARGET) --bench-all --min-size 1000 --max-size 10000 --step 3000 --iterations 1 --output $(DATA_DIR)/quick_results.csv

# Test d'un algorithme spécifique
bench-algo: all
ifndef ALGO
	$(error ALGO n'est pas défini. Usage: make bench-algo ALGO=<nom> SIZE=<taille>)
endif
ifndef SIZE
	$(error SIZE n'est pas défini. Usage: make bench-algo ALGO=<nom> SIZE=<taille>)
endif
	@echo "=== Test de $(ALGO) avec taille $(SIZE) ==="
	@./$(BIN_DIR)/$(TARGET) --bench-algo $(ALGO) --size $(SIZE) --iterations 3 --output $(DATA_DIR)/$(ALGO)_test.csv

# Test des algorithmes O(n²)
bench-quadratic: all
	@echo "=== Test des algorithmes O(n²) ==="
	@for algo in bubble selection insertion; do \
		echo "\n--- $$algo ---"; \
		./$(BIN_DIR)/$(TARGET) --bench-algo $$algo --size 10000 --iterations 2 --output $(DATA_DIR)/quadratic.csv; \
	done

# Test des algorithmes O(n log n)
bench-nlogn: all
	@echo "=== Test des algorithmes O(n log n) ==="
	@for algo in heap merge quick; do \
		echo "\n--- $$algo ---"; \
		./$(BIN_DIR)/$(TARGET) --bench-algo $$algo --size 100000 --iterations 2 --output $(DATA_DIR)/nlogn.csv; \
	done

# ============================================
# COMMANDES DE VISUALISATION
# ============================================

# Générer les graphiques
plot:
	@echo "Génération des graphiques..."
	@if command -v gnuplot >/dev/null 2>&1; then \
		echo "set terminal pngcairo size 1280,720 enhanced font 'Verdana,10'" > $(PLOTS_DIR)/plot.gp; \
		echo "set datafile separator ','" >> $(PLOTS_DIR)/plot.gp; \
		echo "set output 'all_algorithms.png'" >> $(PLOTS_DIR)/plot.gp; \
		echo "set title 'Performance des Algorithmes de Tri'" >> $(PLOTS_DIR)/plot.gp; \
		echo "set xlabel 'Taille du Tableau (éléments)'" >> $(PLOTS_DIR)/plot.gp; \
		echo "set ylabel 'Temps d'\''Exécution (secondes)'" >> $(PLOTS_DIR)/plot.gp; \
		echo "set grid" >> $(PLOTS_DIR)/plot.gp; \
		echo "set logscale y" >> $(PLOTS_DIR)/plot.gp; \
		echo "set key outside right top" >> $(PLOTS_DIR)/plot.gp; \
		echo "plot for [i=0:20] '../data/results.csv' every ::1 using 2:($$1 eq word('bubble,selection,insertion,shell,heap,merge,quick,comb,cocktail,cycle,gnome,tim,counting,radix,bucket,pigeonhole,bitonic,stooge,oddeven,strand,intro', i+1) ? $$3 : 1/0) title word('Bubble,Selection,Insertion,Shell,Heap,Merge,Quick,Comb,Cocktail,Cycle,Gnome,Tim,Counting,Radix,Bucket,Pigeonhole,Bitonic,Stooge,OddEven,Strand,Intro', i+1) with linespoints" >> $(PLOTS_DIR)/plot.gp; \
		cd $(PLOTS_DIR) && gnuplot plot.gp; \
		echo "Graphiques générés dans $(PLOTS_DIR)/"; \
	else \
		echo "Gnuplot n'est pas installé. Installation: sudo apt-get install gnuplot"; \
	fi

# Générer un graphique simple (fallback)
plot-simple: plot

# Benchmark complet avec graphiques
bench-plot: bench-full plot

# ============================================
# COMMANDES DE TEST
# ============================================

# Test de validation rapide
test-quick: all
	@echo "=== Test de validation rapide ==="
	@./$(BIN_DIR)/$(TARGET) --bench-algo quick --size 10000 --iterations 1 --output /dev/null
	@./$(BIN_DIR)/$(TARGET) --bench-algo bubble --size 1000 --iterations 1 --output /dev/null

# Vérifier que les algorithmes trient correctement
test-validate: all
	@echo "=== Validation du tri ==="
	@for size in 1000 5000 10000; do \
		echo "\nTaille: $$size"; \
		for algo in bubble insertion quick; do \
			echo -n "  $$algo: "; \
			./$(BIN_DIR)/$(TARGET) --bench-algo $$algo --size $$size --iterations 1 --output /dev/null 2>&1 | grep -q "✓" && echo "OK" || echo "ÉCHEC"; \
		done; \
	done

# ============================================
# COMMANDES UTILITAIRES
# ============================================

# Mode interactif
run: all
	./$(BIN_DIR)/$(TARGET)

# Afficher les résultats CSV
show-results:
	@if [ -f "$(DATA_DIR)/results.csv" ]; then \
		echo "=== 10 premières lignes de $(DATA_DIR)/results.csv ==="; \
		head -n 20 $(DATA_DIR)/results.csv; \
		echo "..."; \
		wc -l $(DATA_DIR)/results.csv; \
	else \
		echo "Aucun fichier results.csv trouvé."; \
	fi

# Vérifier l'intégrité des données
check-data:
	@echo "=== Vérification des données ==="
	@if [ -f "$(DATA_DIR)/results.csv" ]; then \
		echo "Fichier: $(DATA_DIR)/results.csv"; \
		echo "Lignes: $$(wc -l < $(DATA_DIR)/results.csv)"; \
		echo "Algorithmes uniques: $$(tail -n +2 $(DATA_DIR)/results.csv | cut -d, -f1 | sort -u | wc -l)"; \
		echo "Tailles uniques: $$(tail -n +2 $(DATA_DIR)/results.csv | cut -d, -f2 | sort -nu | wc -l)"; \
		echo "Premières données:"; \
		head -n 5 $(DATA_DIR)/results.csv; \
	else \
		echo "Aucune donnée disponible."; \
	fi

# Aide
help:
	@echo "Commandes disponibles:"
	@echo ""
	@echo "Compilation:"
	@echo "  make all              - Compile le projet"
	@echo "  make clean            - Nettoie les fichiers de compilation"
	@echo "  make clean-all        - Nettoie tout (compilation + données)"
	@echo ""
	@echo "Benchmarks:"
	@echo "  make bench-full       - Benchmark complet (1000-50000)"
	@echo "  make bench-quick      - Benchmark rapide"
	@echo "  make bench-algo       - Test spécifique (ALGO=<nom> SIZE=<taille>)"
	@echo "  make bench-quadratic  - Test des algorithmes O(n²)"
	@echo "  make bench-nlogn      - Test des algorithmes O(n log n)"
	@echo ""
	@echo "Visualisation:"
	@echo "  make plot             - Génère les graphiques (nécessite gnuplot)"
	@echo "  make plot-simple      - Génère un graphique simple"
	@echo "  make bench-plot       - Benchmark complet + graphiques"
	@echo ""
	@echo "Tests:"
	@echo "  make test-quick       - Test de validation rapide"
	@echo "  make test-validate    - Vérification du tri"
	@echo ""
	@echo "Utilitaires:"
	@echo "  make run              - Mode interactif"
	@echo "  make show-results     - Affiche les résultats"
	@echo "  make check-data       - Vérifie l'intégrité des données"
	@echo ""
	@echo "Exemples:"
	@echo "  make bench-algo ALGO=quick SIZE=100000"
	@echo "  make bench-plot"
	@echo "  make test-validate"

.PHONY: all directories clean clean-all bench-full bench-quick bench-algo bench-quadratic bench-nlogn plot plot-simple bench-plot test-quick test-validate run show-results check-data help
