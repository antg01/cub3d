/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:56:02 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/28 17:48:35 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Extrait une valeur numérique de couleur à partir d'une chaîne,
** en gérant les espaces.
*/
static int	extract_color_value(t_mlx *data, char *str, t_color_parse *state,
		char *error_msg)
{
	int	value;

	while (str[state->i] == ' ' || str[state->i] == '\t')
		state->i++;
	if (str[state->i] < '0' || str[state->i] > '9')
		my_exit(error_msg, data);
	value = ft_atoi(str + state->i);
	while (str[state->i] >= '0' && str[state->i] <= '9')
		state->i++;
	return (value);
}

/*
** Vérifie la présence d'une virgule dans la chaîne et met à jour l'état.
*/
static void	check_comma(t_mlx *data, char *str, t_color_parse *state, char *error_msg)
{
	while (str[state->i] == ' ' || str[state->i] == '\t')
		state->i++;
	if (str[state->i] != ',')
		my_exit(error_msg, data);
	state->comma_count++;
	state->i++;
}

/*
** Convertit une chaîne de valeurs RGB en un entier
** hexadécimal après vérifications.
*/
unsigned int	str_to_hexa(t_mlx *data, char *str)
{
	t_color_parse	state;
	int				r;
	int				g;
	int				b;

	state.i = 0;
	state.comma_count = 0;
	r = extract_color_value(data, str, &state, "Error: Missing or invalid red value");
	check_comma(data, str, &state, "Error: Missing first comma");
	g = extract_color_value(data, str, &state,
			"Error: Missing or invalid green value");
	check_comma(data, str, &state, "Error: Missing second comma");
	b = extract_color_value(data, str, &state,
			"Error: Missing or invalid blue value");
	while (str[state.i] == ' ' || str[state.i] == '\t')
		state.i++;
	if (str[state.i] != '\0' && str[state.i] != '\n')
		my_exit("Error: Too many values or invalid character", data);
	if (state.comma_count != 2)
		my_exit("Error: Incorrect comma count", data);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		my_exit("Error: Color value out of range (0-255)", data);
	return ((r << 16) | (g << 8) | b);
}
