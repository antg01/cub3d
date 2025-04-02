/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2025/04/02 17:37:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

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
typedef struct s_maplist
{
	char				*line;
	struct s_maplist	*next;
}						t_maplist;
typedef struct s_extract_state
{
	char				*line;
	int					started;
	int					check_nsew;
	t_maplist			*curr;
}						t_extract_state;
typedef struct s_element_flags
{
	int					no;
	int					so;
	int					we;
	int					ea;
	int					f;
	int					c;
}						t_element_flags;
typedef struct s_color_parse
{
	int					i;
	int					comma_count;
}						t_color_parse;
typedef struct s_keys
{
	int					forward;
	int					backward;
	int					left;
	int					right;
	int					rotate_left;
	int					rotate_right;
}						t_keys;

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dis;
	int		color;
	double	wall_x;
	int		line_height;
	int		z;
	int		index_texture;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}						t_raycast;

typedef struct s_player
{
	double				x_pos;
	double				y_pos;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	float				rot_speed;
	t_raycast			*ray;
}						t_player;

typedef struct s_img
{
	void				*img_ptr;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*window;
	void				*image;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				**map;
	int					num_rows;
	double				last_frame;
	t_player			*player;
	t_keys				*keys;
	t_img				textures[4];
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	char				orientation[2];
	int					longest_row;
	//...
}						t_mlx;

typedef struct s_grid
{
	int	x;
	int	y;
	int	y_limit;
	int	x_limit;
	int	biggest_line;
}				t_grid;

typedef struct s_loop
{
	double	new_x;
	double	new_y;
	double	current_time;
	double	delta_time;
	double	move_speed;
	double	rot_speed;
	double	save_dir_x;
	double	save_plane_x;
}				t_loop;

/* ********* */
/* FONCTIONS */
/* ********* */

// MLX
void				my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void				handle_mlx(t_mlx *data);
void				clear_image(t_mlx *data, int color);

// PARSING + utils
int					parsing(t_mlx *data, int fd);
char				*trim_spaces_tabs(char *line);
char				*trim_spaces_tabs(char *line);
void				parse_texture_line(t_mlx *data, char *line, int index);
void				parse_color_line(t_mlx *data,
						unsigned int *color, char *line);
void				init_element_flags(t_element_flags *flags);

//PARSING TEXTURE && COLORS
void				check_four_dir(int fd, t_mlx *data);
void				skip_nl(int fd);
void				check_colors(t_mlx *data, int fd);
void				do_textures(t_mlx *data, char *path_texture, int index);
unsigned int		str_to_hexa(t_mlx *data, char *str);

// MAP
char				**make_map(t_maplist *head, int num_rows, int *longest_row);

// EXTRACT MAP + utils
t_maplist			*extract_map(t_mlx *data, int fd, int *count_rows);
void				check_map_closed(t_mlx *data, char **map, int num_rows);
int					is_only_spaces(char *line);
void				check_chars(t_mlx *data, char *str, int *check_nsew);

// UTILS
int					num_rows(void);
int					round_float(float nb);
double				get_time_in_seconds(void);
void				free_split(char **map);
void				free_all(t_mlx *data);

// SAFE_UTILS
void				*safe_malloc(size_t size);
char				*safe_strdup(char *str);

// MINIMAP
void				draw_grid(t_mlx *data, int num_rows, int cell_size);
int					render(t_mlx *data);
void				set_biggest_line(t_mlx *data, t_grid *g, int num_rows);
int					norm_fix(t_mlx *data, int dx, int dy, int *xy);
void				set_xy(int *xy, int x, int y);
int					draw_white(t_mlx *data,
						t_grid *g, int cell_size, int num_rows);

// PLAYER
t_player			*init_player(t_mlx *data);
int					check_wall(t_mlx *data, int x, int y);

// RAYS (and NORM)
void				draw_rays(t_mlx *data, t_player *player);
void				set_dir_x_y(t_mlx *data, int *dx, int *dy);

// RAYCASTING NORME
void				calc_wall_height(t_raycast *r);
void				prep_vertical_line(t_mlx *data, t_raycast *r);
void				draw_vertical_line(t_mlx *data, t_raycast *r, int x);

// RAYCASTING
void				init_raycast(t_player *player);
void				render_3d(t_mlx *data);

// SMOOTH MOVE
t_keys				*init_keys(void);
int					key_press(int keycode, t_mlx *data);
int					key_release(int keycode, t_mlx *data);
int					game_loop(t_mlx *data);
void				move_front_back(t_mlx *data, double *new_x,
						double *new_y, double speed);
void				rot(t_mlx *data, double save_dir_x,
						double save_plane_x, double rot_speed);

// TEXTURES
t_img				*init_textures(void);
void				load_textures(t_mlx *data);
int					get_texture_pixel(t_img *texture, int x, int y);

// EXITS
void				my_exit(char *msg, t_mlx *data);

#endif
