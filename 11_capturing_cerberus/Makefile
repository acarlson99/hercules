CC = clang
SRCS = main.c
OFILES = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
SRCDIR = src/
OBJDIR = .obj/
NAME = proxy
DNAME = d_$(NAME)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(addprefix $(OBJDIR), %.o): $(addprefix $(SRCDIR), %.c)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	$(shell \
	if [ -d $(OBJDIR) ]; \
	then \
		: ; \
	else \
		mkdir $(OBJDIR); \
	fi)

j:
	$(CC) $(SRCS) -o $(DNAME)
