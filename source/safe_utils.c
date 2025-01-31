/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:53:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/31 01:01:41 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*safe_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
	{
		write(2, "memory alloc failed, exiting\n", 29);
		exit(EXIT_FAILURE);
	}
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
