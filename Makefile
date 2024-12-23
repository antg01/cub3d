NAME = Cub3d

LIBFT = libft/libft.a

MLX_DIR = ./mlx
MLX_PATH = mlx/libmlx.a
MLX =  -L /usr/lib -lXext -lX11 -lm -lz 
MLX_OBJ = -I/usr/include -Imlx_linux -O3

MLX_LIB = -L $(MLX_DIR) -lmlx

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS =	source/test.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLX_DIR)
	@make bonus -C libft
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLX_LIB) $(MLX) -o $(NAME)

%.o : %.c	
	@$(CC) -o $@ -c $<


fclean : clean
	@make fclean -C libft
	@$(RM) fdf

clean :
	@make clean -C libft
	@$(RM) source/*.o mlx/*.o

re : fclean all
