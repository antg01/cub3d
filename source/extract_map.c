/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:09:01 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/28 15:24:56 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	only_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n' && str[i] != '2' && str[i] != '3')
			return (0);
		i++;
	}
	return (1);
}

int	check_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != 'N')
		{
			if (!(i == (int) (ft_strlen(str) - 1) && str[i] == '\n'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	one_to_three(char c)
{
	if (c < '1' || c > '3')
		return (0);
	else
		return (1);
}

void	extract_map(t_mlx *data, int fd)
{
	char	*line;
	int		i;
	int		player_letter;

	player_letter = 0;
	i = 0;
	while (1)
	{
		
	}
}
