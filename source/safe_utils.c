/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:53:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 12:20:15 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*safe_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
	{
		write(2, "Memory allocation failed, exiting...\n", 37);
		exit(EXIT_FAILURE);
	}
	memset(result, 0, size);
	return (result);
}

char	*safe_strdup(char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (!result)
	{
		write(2, "ft_strdup failed, exiting\n", 26);
		exit(EXIT_FAILURE);
	}
	return (result);
}
