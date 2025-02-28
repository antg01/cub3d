/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/28 18:58:13 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(void)
{
	t_mlx	data;
	int		fd;
	
	fd = open("maps/test.cub", O_RDONLY); //here it must be argv[0] instead
	if (-1 == fd)
		return(write(2, "error opening file\n", 19), 1);
	data.mlx = mlx_init();

	//data.window = mlx_new_window(data.mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Top-Down View");
	//data.image = mlx_new_image(data.mlx, WINDOW_LENGTH, WINDOW_HEIGHT);
	//data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);

	if (!parsing(&data, fd))
		return (close(fd), write(2, "invalid map\n", 12), 1);
	handle_mlx(&data);
	return (0);
}
