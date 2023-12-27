HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS_PATH = srcs/
LIB_PATH  = libc/
LOG_PATH  = log/
INC_PATH  = includes/

SRCS_NAME = main.c \
			malloc.c 

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

LOG_NAME =  show_alloc_mem.c 

INCLUDES =  malloc.h 

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

LIBRARY = $(addprefix $(LIB_PATH), $(LIB_NAME))
LOGS = $(addprefix $(LOG_PATH), $(LOG_NAME))
INCLUDE_PATH = $(addprefix $(INC_PATH), $(INCLUDES))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) -lpthread $^ $(LIBRARY) $(LOGS) -I $(INC_PATH)
	@ln -sf $(NAME) libft_malloc.so

odir:
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCLUDE_PATH)
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I $(INC_PATH)

valgrind:
	make && clear && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./libft_malloc_x86_64_Linux.so 
clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning executable"
	@rm -f $(NAME)
	@rm -f libft_malloc.so

re: fclean all

.PHONY: clean fclean re odir
