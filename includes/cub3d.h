/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/31 01:05:15 by gnyssens         ###   ########.fr       */
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



// STRUCTURES

typedef struct s_data {
    void    *mlx;
    void    *window;
    void    *image;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;


/* ********* */
/* FONCTIONS */
/* ********* */

// PARSING
int		parsing(int fd, char *line, int num_rows);

//MAP
char	**make_map(int num_rows);

// UTILS
int		num_rows(void);

// SAFE_UTILS
void	*safe_malloc(size_t size);
char	*safe_strdup(char *str);

#endif