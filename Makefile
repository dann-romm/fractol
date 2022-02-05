CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
# CFLAGS		= -fsanitize=address

NAME		= fractol

SRCDIR		= ./src/
OBJDIR		= ./obj/
INCDIR		= ./includes/
MLXDIR		= ./mlx/

SRC			= fractol.c formulas.c complex.c fractals.c fractals_newton.c utils.c utils_mlx.c utils_ft.c shift.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCDIR)fractol.h
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

.PHONY: all clean fclean re bonus
