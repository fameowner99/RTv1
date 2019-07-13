NAME = rtv1

CC = gcc

FLAGS = #-Wall -Wextra -Werror 

RM = rm -f

SDL_DIR = ./SDL_LIBRARY/SDL2.framework/Headers

HEADERPATH = -I ./inc -I $(LIB_DIR) -I $(SDL_DIR)

SRC = src/main.c src/object_lst.c src/rt.c src/object_managment.c src/vector_operations.c

LIB_DIR = ./libft/

LIB_FLAGS = -L $(LIB_DIR) -lft

SDL_FLAGS = -framework SDL2 -F SDL_LIBRARY -rpath SDL_LIBRARY

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) all
	$(CC) $(FLAGS) $(OBJ) -o $@ $(SDL_FLAGS) $(LIB_FLAGS)
	
	@echo "rtv1 done."

%.o: %.c
	$(CC) $(HEADERPATH) $(FLAGS)  -o $@ -c $<

clean:
	@make clean -C $(LIB_DIR)
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re: fclean all
