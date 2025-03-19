NAME = Cub3d

LIBFT = libft/libft.a

MLX_DIR = ./mlx
MLX_PATH = mlx/libmlx.a
MLX =  -L /usr/lib -lXext -lX11 -lm -lz
MLX_OBJ = -I/usr/include -Imlx_linux -O3

MLX_LIB = -L $(MLX_DIR) -lmlx

CC = cc

CFLAGS = -Werror -Wall -Wextra -g #-fsanitize=address

RM = rm -rf

SRCS =	source/main.c \
		source/parsing.c \
		source/parsing_utils.c \
		source/utils.c \
		source/map.c \
		source/safe_utils.c \
		source/mlx.c \
		source/player.c \
		source/raycast_norm.c \
		source/raycast.c \
		source/smooth_move.c \
		source/textures.c \
		source/parsing_texture.c \
		source/parsing_colors.c \
		source/extract_map.c \
		source/extract_map_utils.c \
		minimap/top_down_norm.c \
		minimap/top_down.c \
		minimap/rays_norm.c \
		minimap/rays.c \

OBJ_DIR = Objects
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling MLX..."
	@make -s -C $(MLX_DIR) > /dev/null
	@echo "Compiling Libft..."
	@make -s bonus -C libft
	@echo "Building $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLX_LIB) $(MLX) -o $(NAME)
	@echo "Compiled successfully."

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@make -s clean -C libft
	@$(RM) $(OBJ_DIR)
	@$(RM) mlx/*.o
	@if [ -f traces.txt ]; then $(RM) traces.txt; fi
	@if [ -f 0 ]; then $(RM) 0; fi
	@echo "Cleaned successfully."

fclean : clean
	@make -s fclean -C libft
	@$(RM) $(NAME)
	@echo "Program cleaned successfully."

re : fclean all
