# ===========================
# Variables de Compilation
# ===========================
HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -I includes/

LDFLAGS = -shared -fPIC -pthread

SRCS_PATH = srcs/
LIB_PATH  = libc/
LOG_PATH  = log/
TEST_PATH = tests/
INC_PATH  = includes/

SRCS_NAME = malloc.c \
			free.c \
			realloc.c \
			heap_creation.c \
			block_creation.c \
			utils/block_utils.c \
			utils/heap_utils.c 

LIB_NAME =  ft_atoi.c \
			ft_bzero.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c 

LOG_NAME =  show_alloc_mem.c \
			show_alloc_mem_exe.c 

TEST_NAME = test.c

INCLUDES =  malloc.h 

OBJS_PATH = objs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)
SRCS_OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

LIBRARY = $(addprefix $(LIB_PATH), $(LIB_NAME))
LIB_OBJS_NAME = $(LIB_NAME:.c=.o)
LIB_OBJS = $(addprefix $(OBJS_PATH), $(LIB_OBJS_NAME))

LOGS = $(addprefix $(LOG_PATH), $(LOG_NAME))
LOG_OBJS_NAME = $(LOG_NAME:.c=.o)
LOG_OBJS = $(addprefix $(OBJS_PATH), $(LOG_OBJS_NAME))

OBJS = $(SRCS_OBJS) $(LIB_OBJS) $(LOG_OBJS)

INCLUDE_PATH = $(addprefix $(INC_PATH), $(INCLUDES))

# ===========================
# Cibles Phony
# ===========================
.PHONY: all clean fclean re compile_test gdb run valgrind odir

# ===========================
# Cible par Défaut
# ===========================
all: odir $(NAME)

# ===========================
# Compilation de la Bibliothèque
# ===========================
$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $^ -I $(INC_PATH)
	@ln -sf $(NAME) libft_malloc.so

# ===========================
# Création des Répertoires des Objets
# ===========================
odir:
	@mkdir -p $(OBJS_PATH)heap
	@mkdir -p $(OBJS_PATH)block
	@mkdir -p $(OBJS_PATH)utils

# ===========================
# Règles de Compilation Génériques
# ===========================
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

$(OBJS_PATH)%.o: $(LIB_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

$(OBJS_PATH)%.o: $(LOG_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

# ===========================
# Compilation des Tests Spéciaux
# ===========================
test: $(TEST_PATH)test.c $(SRCS)
	@echo " - Compiling test"
	@$(CC) $(CFLAGS) -o $(TEST_PATH)test $(TEST_PATH)test.c $(SRCS) 

test5: $(TEST_PATH)test5.c $(SRCS)
	@echo " - Compiling test5"
	@$(CC) $(CFLAGS) -o $(TEST_PATH)test5 $(TEST_PATH)test5.c $(SRCS) $(LDFLAGS) $(LIBFT_MALLOC)

# ===========================
# Autres Cibles pour les Tests
# ===========================
compile_test: all
	@echo " - Compiling test avec options spéciales"
	gcc -Wall -Wextra -Werror -I includes/ tests/test.c -L. -Wl,-rpath=. -lft_malloc -o tests/a.out

# ===========================
# Exécution des Tests
# ===========================
run:
	LD_PRELOAD=./libft_malloc.so $(TEST_PATH)a.out

# ===========================
# Débogage avec Valgrind
# ===========================
valgrind: all
	@echo " - Running Valgrind on tests/a.out"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all LD_PRELOAD=./libft_malloc.so $(TEST_PATH)a.out

# ===========================
# Débogage avec GDB
# ===========================
gdb: all
	@echo " - Running GDB on tests/a.out"
	gdb -tui $(TEST_PATH)a.out

# ===========================
# Nettoyage des Fichiers Objets et Exécutables
# ===========================
clean:
	@echo " - Cleaning objs"
	@rm -rf $(OBJS_PATH)

fclean: clean
	@echo " - Cleaning executables and library"
	@rm -f $(NAME) libft_malloc.so
	@rm -f $(TEST_PATH)a.out

# ===========================
# Recompilation Complète
# ===========================
re: fclean all
