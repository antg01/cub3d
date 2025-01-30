/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:53:45 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/30 20:01:25 by gnyssens         ###   ########.fr       */
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
