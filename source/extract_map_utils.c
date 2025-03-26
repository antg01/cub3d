/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:57:43 by angerard          #+#    #+#             */
/*   Updated: 2025/03/26 14:47:26 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Vérifie si la ligne ne contient que des espaces,
** tabulations ou sauts de ligne.
*/
int	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/*
** Vérifie que la map est fermée en s’assurant qu’aucun espace ouvert
** n’est présent aux bords ou autour des cases valides.
*/
void	check_map_closed(char **map, int num_rows, int longest_row)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_rows)
	{
		j = 0;
		while (j < longest_row && map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || j == 0 || i == num_rows - 1 || j == (int)ft_strlen(map[i])
					- 1)
					my_exit("Error: Map is not closed (border)");
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
					my_exit("Error: Map is not closed (adjacent to space)");
			}
			j++;
		}
		i++;
	}
}

/*
** Définit l’orientation du joueur selon le caractère rencontré dans la map.
*/
void	which_orien(t_mlx *data, char c)
{
	if (c == 'N')
		*(data->orientation) = 'N';
	else if (c == 'S')
		*(data->orientation) = 'S';
	else if (c == 'E')
		*(data->orientation) = 'E';
	else if (c == 'W')
		*(data->orientation) = 'W';
	*(data->orientation + 1) = '\0';
}

/*
** Vérifie la validité des caractères d'une ligne de map et détecte
** la position du joueur.
*/
void	check_chars(t_mlx *data, char *str, int *check_nsew)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			my_exit("Error: non-valid character in map");
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			which_orien(data, str[i]);
			(*check_nsew)++;
		}
		if (*check_nsew > 1)
			my_exit("Error: Too many player's start positions");
		i++;
	}
}
