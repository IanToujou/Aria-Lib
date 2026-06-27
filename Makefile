NAME = arialib.a

SRC = src/argument.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -Ofast -march=native -ffast-math -flto
AR = llvm-ar-12 rcs
RANLIB = llvm-ranlib-12

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $@ $^
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