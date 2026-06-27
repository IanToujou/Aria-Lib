NAME = libaria.a

SRC = src/argument.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -O3 -march=native -ffast-math -flto
AR = $(shell $(CC) -print-prog-name=llvm-ar)
ARFLAGS = rcs
RANLIB = $(shell $(CC) -print-prog-name=llvm-ranlib)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re