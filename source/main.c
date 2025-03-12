/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/05 15:43:40 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(void)
{
	t_mlx	data;
	int		fd;

	fd = open("maps/test.cub", O_RDONLY);
	if (-1 == fd)
		return(write(2, "error opening file\n", 19), 1);
	data.mlx = mlx_init();

	if (!parsing(&data, fd))
		return (close(fd), write(2, "invalid map\n", 12), 1);
	handle_mlx(&data);
	return (0);
}
