NAME    = philo

# Compiler and flags.
CC      = cc
CFLAGS  = -Wall -Wextra -Werror #-fsanitize=thread
LDFLAGS = -pthread

# Source files in the project.
SRC     = main.c \
		  init.c libft_utils.c start.c routine.c parser.c\
			checker.c routine_utils.c errors.c
# All source files.
ALL_SRC = $(SRC)

# Object files (will be created in the same directory).
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
