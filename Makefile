NAME        = philosophers

# Dossiers
PATH_SRC    = src/
PATH_INC    = includes/

CC          = cc
FLAGS       = -Wall -Wextra -Werror -g3 -fPIE
INCLUDES    = -I $(PATH_INC)

SRC_FILES   = utils.c \
			simulation.c \
			time.c\
			main.c \
	
OBJ         = $(addprefix $(PATH_SRC), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lm -o $(NAME)
	@echo "$(NAME) compiled"

$(PATH_SRC)%.o: $(PATH_SRC)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@echo "🧹 Objects cleaned."

fclean: clean
	@/bin/rm -f $(NAME)
	@echo " $(NAME) deleted."

re: fclean all

.PHONY: all clean fclean re