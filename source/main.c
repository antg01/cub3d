/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/28 15:59:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(void)
{
	t_mlx	mlx;
	int		fd;
	
	fd = open("maps/test.cub", O_RDONLY); //here it must be argv[0] instead
	if (-1 == fd)
		return(write(2, "error opening file\n", 19), 1);
	mlx.mlx = mlx_init();
	if (!parsing(&mlx, fd))
		return (close(fd), write(2, "invalid map\n", 12), 1);
	mlx.map = make_map(mlx.num_rows); //ICI GRAND PROBLEME, PCQ GNL DEVRA REPASSER PAR LE RESTE
	handle_mlx(&mlx);
	return (0);
}
