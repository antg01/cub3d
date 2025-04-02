/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:57:43 by angerard          #+#    #+#             */
/*   Updated: 2025/04/02 16:09:59 by gnyssens         ###   ########.fr       */
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

int	is_open_space(char **map, int row, int col, int num_rows)
{
	int row_len;

	// If row out of range => open
	if (row < 0 || row >= num_rows)
		return (1);

	row_len = ft_strlen(map[row]);
	// If col out of range for that row => open
	if (col < 0 || col >= row_len)
		return (1);

	// If the char is ' ' => open
	if (map[row][col] == ' ')
		return (1);

	// Otherwise, it's presumably a '1' or something else => not open
	return (0);
}


/*
** Vérifie que la map est fermée en s’assurant qu’aucun espace ouvert
** n’est présent aux bords ou autour des cases valides.
*/
void	check_map_closed(t_mlx *data, char **map, int num_rows)
{
	for (int i = 0; i < num_rows; i++)
	{
		int row_len = ft_strlen(map[i]);  // length of this specific row
		for (int j = 0; j < row_len; j++)
		{
			char c = map[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				// 1) If on the outer boundary => not closed
				if (i == 0 || i == num_rows - 1 || j == 0 || j == row_len - 1)
					my_exit("Error: Map isn't closed (border)", data);

				// 2) Check each neighbor
				//    If out of range or ' ' => not closed
				if (is_open_space(map, i - 1, j, num_rows))  // up
					my_exit("Error: Map isn't closed (space above)", data);
				if (is_open_space(map, i + 1, j, num_rows))  // down
					my_exit("Error: Map isn't closed (space below)", data);
				if (is_open_space(map, i, j - 1, num_rows))  // left
					my_exit("Error: Map isn't closed (space left)", data);
				if (is_open_space(map, i, j + 1, num_rows))  // right
					my_exit("Error: Map isn't closed (space right)", data);
			}
		}
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
			my_exit("Error: non-valid character in map", data);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			which_orien(data, str[i]);
			(*check_nsew)++;
		}
		if (*check_nsew > 1)
			my_exit("Error: Too many player's start positions", data);
		i++;
	}
}
