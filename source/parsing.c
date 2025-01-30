/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:31 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/30 19:16:13 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	only_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n')
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

/*
int	check_if_last(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || *line == '\0')
	{
		if (line)
			free(line);
		return (1);
	}
	else
	{
		free(line);
		return (0);
	}
}
*/

//ya encore des pb, devrait pas pouvoir y avoir plusieurs 'N', et faut checker si la forme de la map a un sens
//si une row a longueur 5, la suivante doit avoir longueur 3, 5 ou 7 !
int	parsing(int fd, char *line, int num_rows)
{ //parametre *line doit etre égal à NULL !!
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || *line == '\0')
			break;
		if (0 == i || num_rows - 1 == i)
		{
			if (!only_ones(line))
			{
				if (line)
					free(line);
				return(write(2, "1 invalid map\n", 14), 0);
			}
		}
		else 
		{
			if (only_ones(line))
				return(free(line), write(2, "2 invalid map\n", 14), 0);
			else
			{
				if (line[0] != '1' || line [ft_strlen(line) - 2] != '1') //-2 pcq [-1] cest \n
					return(free(line), write(2, "3 invalid map\n", 14), 0);
				if (!check_chars(line))
					return(free(line), write(2, "4 invalid map\n", 14), 0);
			}
		}
		free(line);
		i++;
	}
	return (1);
}
