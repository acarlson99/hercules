CC := clang
CFLAGS := -Wall -Wextra -Werror -Wpedantic
DFLAGS := -Wall -Wextra -Wpedantic -g
CFILES := main.c aux.c
OFILES := $(CFILES:.c=.o)
SRC := src/
NAME := hydra
DNAME := d_$(NAME)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

j:
	$(CC) $(DFLAGS) $(CFILES) -o $(DNAME)

k: fclean
	rm -f $(DNAME)
	rm -rf *.dSYM

l: re

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
