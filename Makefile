NAME = fractol

CC = gcc

FLAGS = #-Wall -Wextra -Werror 

RM = rm -f

HEADERPATH = -I ./inc -I $(LIB_DIR) -I $(MLX_DIR)

SRC = src/main.c src/ft_image.c src/fractol.c src/controls.c src/draw.c \
	src/fractals/mandelbrot.c src/fractals/julia.c src/fractals/burning_ship.c \
	src/mouse_filter.c

LIB_DIR = libft/

LIB_FLAGS = -L $(LIB_DIR) -lft

MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -framework OpenCL

MLX_DIR = minilibx_macos/

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) all
	@make -C $(MLX_DIR) all
	$(CC) $(FLAGS) $(OBJ) -o $@  $(LIB_FLAGS) $(MLX_FLAGS)
	
	@echo "fractol done."

%.o: %.c
	$(CC) $(HEADERPATH) $(FLAGS)  -o $@ -c $<

clean:
	@make clean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(MLX_DIR)
	$(RM) $(NAME)

re: fclean all
