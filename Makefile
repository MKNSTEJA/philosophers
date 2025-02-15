NAME    = philo

# Compiler and flags.
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS = -pthread

# Source files in the project.
SRC     = main.c \
		  init.c libft_utils.c start.c routine.c parser.c\
			checker.c routine_utils.c
# All source files.
ALL_SRC = $(SRC)

# Object files (will be created in the same directory).
OBJ     = $(ALL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
