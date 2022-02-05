CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

NAME		= fractol

SRCDIR		= ./src/
OBJDIR		= ./obj/
INCDIR		= ./includes/

SRC			= fractol.c formulas.c complex.c fractals.c fractals_newton.c utils.c utils_mlx.c utils_ft.c shift.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))
LIB			= ./libmlx.dylib

all: $(LIB) $(NAME)

$(LIB): ./mlx/mlx.h
	make -C ./mlx/
	cp ./mlx/libmlx.dylib $(LIB)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCDIR)fractol.h
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -Imlx -Ofast

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make -C ./mlx/ clean
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
