HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

LDFLAGS = -shared -fPIC -pthread -g3

SRCS_PATH = srcs/
LIB_PATH  = libc/
LOG_PATH  = log/
TEST_PATH = tests/
INC_PATH  = includes/

SRCS_NAME = malloc.c \
			free.c \
			realloc.c \
			heap/heap_creation.c \
			block/block_creation.c \
			  
LIB_NAME =  ft_atoi.c \
			ft_bzero.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \

LOG_NAME =  show_alloc_mem_basic.c \
			show_alloc_mem_exe.c \

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

all: odir $(NAME)

$(NAME): $(OBJS) 
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $^ -I $(INC_PATH)
	@ln -sf $(NAME) libft_malloc.so

odir:
	@mkdir -p $(OBJS_PATH)heap
	@mkdir -p $(OBJS_PATH)block

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

$(OBJS_PATH)%.o: $(LIB_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

$(OBJS_PATH)%.o: $(LOG_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

run:
	cd tests/ && LD_PRELOAD=../libft_malloc.so ../tests/a.out \
	# LD_PRELOAD=./libft_malloc.so tests/a.out

vim:
	LD_PRELOAD=./libft_malloc.so vim test_vim.c

valgrind:
	make && clear && cd tests/ && LD_PRELOAD=../libft_malloc.so valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ../tests/a.out

valgrind_ls:
	make && clear && cd tests/ && LD_PRELOAD=../libft_malloc.so valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all /bin/ls

valgrind_cal:
	make && clear && cd tests/ && LD_PRELOAD=../libft_malloc.so valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all cal

valgrind_echo:
	make && clear && cd tests/ && LD_PRELOAD=../libft_malloc.so valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all echo "bonjour"

gdb:
	make && clear && gdb -tui a.out

compile_test: all
	gcc -Wall -Wextra -Werror -I includes/ tests/test.c -L. -Wl,-rpath=.. -lft_malloc -o tests/a.out

clean:
	@echo " - Cleaning objs"
	@rm -rf objs
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning executable"
	@rm -f $(NAME)
	@rm -f libft_malloc.so

re: fclean all

.PHONY: clean fclean re odir
