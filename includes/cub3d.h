/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/06 15:46:02 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <X11/keysym.h> //pas sur a 100%
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define WINDOW_HEIGHT 800
# define WINDOW_LENGTH 1000
# define IMAGE_HEIGHT 600
# define IMAGE_LENGTH 600
# define GRAY 0x808080
# define PI 3.14159265


// STRUCTURES

typedef struct  s_player {
	double	x_pos;         // Player's X position (continuous, not limited to grid cells)
	double	y_pos;         // Player's Y position
	double	dir_x;     // Player's direction vector X
	double	dir_y;     // Player's direction vector Y
	double	plane_x;   // Camera plane X (for FOV projection)
	double	plane_y;   // Camera plane Y
	float	rot_speed;
}               t_player;

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
	t_player	*player;
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
int		parsing(int fd, char *line, int num_rows);

// MAP
char	**make_map(int num_rows);

// UTILS
int		num_rows(void);
int		round_float(float nb);

// SAFE_UTILS
void	*safe_malloc(size_t size);
char	*safe_strdup(char *str);

// TOP-DOWN
void 	draw_grid(t_mlx *data, int num_rows);
int		render(t_mlx *data);

// PLAYER
t_player	*init_player(t_mlx *data);
int			check_wall(t_mlx *data, float x, float y);

// RAYS
void	draw_rays(t_mlx *data, t_player *player);

#endif