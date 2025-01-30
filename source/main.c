/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/30 15:27:45 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int main(void)
{
	int		fd;
	
	fd = open("map.cub", O_RDONLY);
	if (-1 == fd)
		return(write(2, "error opening file\n", 19), 0);
	
}
