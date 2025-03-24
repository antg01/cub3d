/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:59:00 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/24 15:20:25 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	free_split(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_all(t_mlx *data)
{
	int	i;

	i = 0;
	if (data->map)
		free_split(data->map);
	if (data->player)
		free(data->player);
	if (data->keys)
		free(data->keys);
	while (i < 4)
	{
		if (data->textures[i].img_ptr)
			mlx_destroy_image(data->mlx, data->textures[i].img_ptr);
		i++;
	}
	if (data->hand->img_ptr)
		mlx_destroy_image(data->mlx, data->hand->img_ptr);
	if (data->image)
		mlx_destroy_image(data->mlx, data->image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_maplist(t_maplist *head)
{
	t_maplist	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->line)
			free(temp->line);
		free(temp);
	}
}
