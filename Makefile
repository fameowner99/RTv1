NAME = rtv1

CC = gcc

FLAGS = #-Wall -Wextra -Werror 

RM = rm -f

SDL_INC = #./SDL_LIBRARY/SDL2.framework/Headers

LIBVEC_INC = ./libvec/inc/

LIB_DIR = ./libft/

LIBVEC_DIR = ./libvec/

HEADERPATH = -I ./inc -I $(LIB_DIR) -I $(SDL_INC)  $(LIBVEC_INC)

SRC = src/main.c src/object_lst.c src/rt.c src/object_managment.c src/renderer.c src/ray_handler.c \
	src/event_handler.c src/camera_manipulator.c src/light_lst.c

LIBVEC_FLAGS = -L $(LIBVEC_DIR) -lvec

LIB_FLAGS = -L $(LIB_DIR) -lft

SDL_FLAGS = #-framework SDL2 #-F SDL_LIBRARY -rpath SDL_LIBRARY

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) all
	@make -C $(LIBVEC_DIR) all
	$(CC) $(FLAGS) $(OBJ) -o $@ $(SDL_FLAGS) $(LIB_FLAGS) $(LIBVEC_FLAGS) -lSDL2
	
	@echo "rtv1 done."

%.o: %.c
	$(CC) $(HEADERPATH) $(FLAGS)  -o $@ -c $<

clean:
	@make clean -C $(LIB_DIR)
	@make clean -C $(LIBVEC_DIR)
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(LIBVEC_DIR)
	$(RM) $(NAME)

re: fclean all
