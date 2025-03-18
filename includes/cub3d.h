/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 14:23:44 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <sys/types.h>

# define IMAGE_HEIGHT 500
# define IMAGE_LENGTH 500
# define WINDOW_HEIGHT 1200
# define WINDOW_LENGTH 2000
# define GRAY 0x808080
# define RED 0xFF0000
# define DARK_RED 0x8B0000
# define BLUE 0X444FF
# define DARK_BLUE 0X0000B9
# define GREEN 0X00FF00
# define DARK_GREEN 0X00CA00
# define BROWN 0x483C32
# define SKY 0x90D5FF
# define PI 3.14159265


// STRUCTURES

typedef struct s_maplist {
	char				*line;
	struct s_maplist	*next;
}				t_maplist;

typedef struct s_keys {
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}				t_keys;

typedef struct s_raycast {
	double	pl_x_pos;
	double	pl_y_pos;
	double	dir_x;     // Player's direction vector X
	double	dir_y;     // Player's direction vector Y
	double	plane_x;   // Camera plane X (for FOV projection)
	double	plane_y;   // Camera plane Y
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
}				t_raycast;

typedef struct  s_player {
	double		x_pos;         // Player's X position (continuous, not limited to grid cells)
	double		y_pos;         // Player's Y position
	double		dir_x;     // Player's direction vector X
	double		dir_y;     // Player's direction vector Y
	double		plane_x;   // Camera plane X (for FOV projection)
	double		plane_y;   // Camera plane Y
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	float		rot_speed;
	t_raycast	*ray;
}               t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
	//char	*path; //path pr textures/"exemple.xpm"
}				t_img;


typedef struct s_mlx {
    void    	*mlx;
    void    	*window;
    void    	*image;
    char    	*addr;
    int     	bits_per_pixel;
    int     	line_length;
    int     	endian;
	char		**map;
	int			num_rows; //temporaire, map sera pas forcément carrée
	double		last_frame;
	t_player	*player;
	t_keys		*keys;
	t_img		textures[4]; //pr linstant juste 1, pr tester brick
	t_img		hand[1];
	unsigned int			floor_color;
	unsigned int			ceiling_color;
	char		orientation[2];
	int			longest_row;
    //...
} t_mlx;

/* ********* */
/* FONCTIONS */
/* ********* */

// MLX
void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	handle_mlx(t_mlx *data);
void 	clear_image(t_mlx *data, int color);

// PARSING
int		parsing(t_mlx *data, int fd);
char *trim_spaces_tabs(char *line);

//PARSING TEXTURE && COLORS
void	check_four_dir(int fd, t_mlx *data);
void	my_exit(char *msg);
void	skip_nl(int fd);
void	check_colors(t_mlx *data, int fd);
void	do_textures(t_mlx *data, char *path_texture, int index);
unsigned int	str_to_hexa(char *str);

// MAP
char	**make_map(t_maplist *head, int num_rows, int *longest_row);

// EXTRACT MAP
t_maplist	*extract_map(t_mlx *data, int fd, int *count_rows);
void check_map_closed(char **map, int num_rows, int longest_row);

// UTILS
int		num_rows(void);
int		round_float(float nb);
double	get_time_in_seconds(void);
void	free_split(char **map);
void	free_all(t_mlx *data);

// SAFE_UTILS
void	*safe_malloc(size_t size);
char	*safe_strdup(char *str);

// TOP-DOWN
void 	draw_grid(t_mlx *data, int num_rows);
int		render(t_mlx *data);

// PLAYER
t_player	*init_player(t_mlx *data);
int			check_wall(t_mlx *data, int x, int y);

// RAYS
void	draw_rays(t_mlx *data, t_player *player);

// RAYCASTING
void	init_raycast(t_player *player);
void	render_3d(t_mlx *data); //CHATGPT, attention juste checker

// SMOOTH MOVE
t_keys	*init_keys(void);
int		key_press(int keycode, t_mlx *data);
int		key_release(int keycode, t_mlx *data);
int		game_loop(t_mlx *data);

// TEXTURES
t_img	*init_textures(void);
void	load_textures(t_mlx *data);
int 	get_texture_pixel(t_img *texture, int x, int y);
void	load_handgun(t_mlx *data);

#endif
