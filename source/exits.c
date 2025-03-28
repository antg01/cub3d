/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:34:25 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/28 15:43:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_exit(char *msg, t_mlx *data)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_all(data);
	exit(EXIT_FAILURE);
}

/*
void	my_exit2(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
*/