NAME	= libasm_tester
NAME_BONUS  = libasm_tester_bonus

SRCS	= test/main.c \
		  test/ft_strlen_tester.c \
		    test/ft_strcpy_tester.c \
		    test/ft_strcmp_tester.c \
		    test/ft_write_tester.c \
		    test/ft_read_tester.c \
		    test/ft_strdup_tester.c 


BONUS_SRCS = bonus/main_bonus.c \
             bonus/ft_list_push_front_tester.c \
             bonus/ft_list_size_tester.c 

HEADER	= -I ./functions/includes/ \
		  -I ./libasm_tester \
		  -I ./bonus/libasm_tester_bonus \

OBJS	= $(SRCS:test/%.c=obj/%.o)

OBJS_BONUS =  $(BONUS_SRCS:bonus/%.c=obj_bonus/%.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

all:	obj $(NAME)

$(NAME): $(OBJS) functions/libasm.a
	@ $(CC) $(CFLAGS) -o $@ $(OBJS) functions/libasm.a


$(NAME_BONUS): $(OBJS_BONUS) functions/libasm_bonus.a
	@ $(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) functions/libasm_bonus.a

bonus: obj_bonus $(NAME_BONUS)

obj:
	@ mkdir -p obj

obj_bonus:
	@ mkdir -p obj_bonus

obj/%.o:	test/%.c
		${CC} ${CFLAGS} -I. -c $< -o $@

obj_bonus/%.o:    bonus/%.c
		${CC} ${CFLAGS} -I. -c $< -o libasm_tester_bonus

functions/libasm.a:
	make -C functions/

functions/libasm_bonus.a:
	make bonus -C functions/

clean:
	@printf "%b" "\t    $(_PURPLE)[Cleaning] $(_PURPLE)[all]$(_PINK_ORANGE)\n";
	rm -rf obj
	rm -rf obj_bonus
	rm -rf functions/obj
	rm -rf functions/obj_bonus

fclean: clean
	@printf "%b" "\t    $(_ORANGE)[Cleaning] $(_ORANGE)[all]$(_RED)\n";
	rm -f $(NAME)
	rm -rf functions/libasm.a
	rm -rf functions/libasm_bonus.a

re:		fclean all

.PHONY:		all clean fclean re valgrind

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
