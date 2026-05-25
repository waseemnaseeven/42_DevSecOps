NAME       = woody_woodpacker

CC         = gcc
CFLAGS     = -Wall -Wextra -Werror -O2 -I includes

AS         = nasm
ASFLAGS64  = -f bin
ASFLAGS32  = -f bin -DBITS32

SRCDIR     = srcs
ASMDIR     = srcs/asm
OBJDIR     = obj

SRCS       = $(SRCDIR)/main.c        \
             $(SRCDIR)/crypto.c      \
             $(SRCDIR)/file_io.c
#               $(SRCDIR)/elf_parse.c   \
#              $(SRCDIR)/stub_inject.c \

# STUB64_SRC = $(ASMDIR)/woody_stub.s
# STUB64_BIN = $(ASMDIR)/woody_stub64.bin
# STUB32_BIN = $(ASMDIR)/woody_stub32.bin

OBJS       = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(STUB64_BIN) $(STUB32_BIN) $(OBJDIR) $(NAME)

$(STUB64_BIN): $(STUB64_SRC)
	$(AS) $(ASFLAGS64) -o $@ $<

$(STUB32_BIN): $(STUB64_SRC)
	$(AS) $(ASFLAGS32) -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(STUB64_BIN) $(STUB32_BIN)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(STUB64_BIN) $(STUB32_BIN)

fclean: clean
	rm -f $(NAME) woody

re: fclean all

test: all
	bash tests/run_tests.sh

.PHONY: all clean fclean re test