NAME	= libasm.a

SRCS	= srcs/ft_strlen.s \
		  srcs/ft_strcpy.s \
		  srcs/ft_strcmp.s \
		  srcs/ft_write.s \
		  srcs/ft_read.s \
		  srcs/ft_strdup.s

BNS		= bonus/ft_list_push_front.s \
		  bonus/ft_list_size.s \
		  bonus/ft_list_sort.s \
		  bonus/ft_list_remove_if.s


HEADER	= libasm.h

OBJS	= $(SRCS:srcs/%.s=obj/%.o)

LIB 	= ar rcs

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
