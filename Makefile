CC			= gcc
RM			= rm -rf
# CFLAGS		= -Wall -Wextra -Werror
# CFLAGS		= -fsanitize=address

NAME		= fractol

SRCDIR		= ./src/
OBJDIR		= ./obj/
INCDIR		= ./includes/
MLXDIR		= ./mlx/

SRC			= fractol.c formulas.c complex.c fractals.c utils.c utils_mlx.c shift.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -Imlx -Ofast

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUSNAME)

re: fclean all

bonus: $(NAME)

clear:
	clear

# t: clear $(NAME)
# 	@echo "____________________"
# 	@echo $(NAME)
# 	@echo "____________________"
# 	@./$(NAME) 

# p: $(NAME) $(BONUSNAME)
# 	python3 temp.py

.PHONY: all clean fclean re bonus
