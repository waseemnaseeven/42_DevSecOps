NAME	= libasm_tester

SRCS	= test/main.c \
		  test/ft_strlen_tester.c \
		#   test/ft_strcpy_tester.c \
		#   test/ft_strcmp_tester.c \
		#   test/ft_write_tester.c \
		#   test/ft_read_tester.c \
		#   test/ft_strdup_tester.c

BNS		= bonus/ft_list_push_front_test.c \
		  bonus/ft_list_size_test.c \
		  bonus/ft_list_sort_test.c \
		  bonus/ft_list_remove_if_test.c 

HEADER	= libasm_tester.h

OBJS	= $(SRCS:srcs/%.c=obj/%.o)

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g3

all:	obj $(NAME)

$(NAME): $(OBJS)
		@ $(CC) $(CFLAGS) -o $(NAME) $^

obj:
		@mkdir -p obj

obj/%.o:	srcs/%.c
		${CC} ${CFLAGS} -I. -c $< -o $@

valgrind:
	make && clear && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes 

clean:
	@printf "%b" "\t    $(_PURPLE)[Cleaning] $(_PURPLE)[all]$(_PINK_ORANGE)\n";
	rm -rf obj

fclean: clean
	@printf "%b" "\t    $(_ORANGE)[Cleaning] $(_ORANGE)[all]$(_RED)\n";
	rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

# -------------- Syntaxing -------------- #

_NO                    =        \033[0m
_BOLD                =        \033[1m
_BLUE                =        \033[34m
_CYAN                =        \033[36m
_RED                =        \033[31m
_PURPLE             =        \033[35m
_PINK_ORANGE        =        \033[38;5;215m
_GREY                 =        \033[38;5;234m
_STARLIGHT_BLUE     =        \033[38;5;158m
_STARLIGHT_GREEN    =        \033[38;5;157m
_DEEP_BLUE            =        \033[38;5;69m
_YELLOW             =        \033[38;5;226m
_ORANGE                =         \033[38;5;209m\e[1m

# -------------- Syntaxing -------------- #
