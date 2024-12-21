
CC = gcc
CFLAGS = -g3 -I ../includes/
LIBFT_MALLOC = -L.. -lft_malloc

TESTS_DIR = .
SRC_DIR = ../srcs

# ===========================
# Listes de Tests
# ===========================
REGULAR_TESTS = test0 test1 test2 test3 test3_plus test4
SPECIAL_TESTS = test test5

# ===========================
# Sources Additionnelles pour Tests Spéciaux
# ===========================
SPECIAL_SRC = $(SRC_DIR)/malloc.c $(SRC_DIR)/realloc.c $(SRC_DIR)/free.c

# ===========================
# Cibles Phony
# ===========================
.PHONY: all clean fclean re compile_test gdb run valgrind

# ===========================
# Cible par Défaut
# ===========================
all: $(addprefix $(TESTS_DIR)/, $(REGULAR_TESTS)) $(addprefix $(TESTS_DIR)/, $(SPECIAL_TESTS))

# ===========================
# Compilation des Tests Réguliers
# ===========================
$(TESTS_DIR)/%: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# ===========================
# Compilation du Test 'test' avec Sources Additionnelles
# ===========================
$(TESTS_DIR)/test: $(TESTS_DIR)/test.c $(SPECIAL_SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

# ===========================
# Compilation du Test 'test5' avec Sources Additionnelles et Libft_malloc
# ===========================
$(TESTS_DIR)/test5: $(TESTS_DIR)/test5.c $(SPECIAL_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_MALLOC)

# ===========================
# Nettoyage des Exécutables
# ===========================
clean:
	rm -f $(addprefix $(TESTS_DIR)/, $(REGULAR_TESTS)) $(addprefix $(TESTS_DIR)/, $(SPECIAL_TESTS))

# ===========================
# Nettoyage Complet
# ===========================
fclean: clean

# ===========================
# Recompilation Complète
# ===========================
re: fclean all

# ===========================
# Compilation Spécifique avec Rpath (Optionnelle)
# ===========================
compile_test: all
	$(CC) $(CFLAGS) -I ../includes/ test.c ../srcs/malloc.c ../srcs/realloc.c ../srcs/free.c -L.. -Wl,-rpath.. -lft_malloc -o a.out

# ===========================
# Débogage avec GDB
# ===========================
gdb: all
	gdb -tui ./a.out

# ===========================
# Exécution avec Valgrind
# ===========================
valgrind: all
	LD_PRELOAD=../libft_malloc.so valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./test5
