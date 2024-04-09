NAME        = libasm.a
NAME_BONUS  = libasm_bonus.a

SRCS        = srcs/ft_strlen.s \
              srcs/ft_strcpy.s \
              srcs/ft_strcmp.s \
              srcs/ft_write.s \
              srcs/ft_read.s \
              srcs/ft_strdup.s

BNS         = bonus/ft_list_push_front.s \
              bonus/ft_list_size.s

HEADER      = -I ./includes/libasm

HEADER_BONUS = -I ./includes/libasm_bonus

OBJS        = $(SRCS:srcs/%.s=obj/%.o)

OBJS_BONUS  = $(BNS:bonus/%.s=obj_bonus/%.o)

LIB         = ar
LIBFLAGS    = -rcs

ASM         = nasm
FLAGS       = -f elf64

all: obj obj_bonus $(NAME)

$(NAME): $(OBJS)
	$(LIB) $(LIBFLAGS) $(NAME) $(OBJS)

$(NAME_BONUS): $(OBJS_BONUS) 
	$(LIB) $(LIBFLAGS) $(NAME_BONUS) $(OBJS_BONUS)

bonus: obj_bonus $(NAME_BONUS)

obj:
	mkdir -p obj

obj_bonus:
	mkdir -p obj_bonus

obj/%.o: srcs/%.s
	$(ASM) $(FLAGS) $< -o $@ $(HEADER)

obj_bonus/%.o: bonus/%.s
	$(ASM) $(FLAGS) $< -o $@ $(HEADER_BONUS)

clean:
	@printf "%b" "\t    $(_ORANGE)[Cleaning] $(_ORANGE)[all]$(_PINK_ORANGE)\n";
	rm -rf obj obj_bonus

fclean: clean
	@printf "%b" "\t    $(_STARLIGHT_BLUE)[Cleaning] $(_STARLIGHT_BLUE)[all]$(_BLUE)\n";
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re

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
