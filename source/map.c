/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:35 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/04 13:59:02 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**make_map(int num_rows)
{
	char	**result;
	char	*line;
	int		fd;
	int		i;

	result = (char **) safe_malloc((size_t) (sizeof(char *) * (num_rows + 1))); // + 1 pr NULL
	fd = open("maps/test.cub", O_RDONLY);
	if (-1 == fd)
	{
		write(2, "file opening failed (exiting)\n", 31);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line) // || *line == '\0' ?
			break;
		result[i] = safe_strdup(line);
		free(line);
		i++;
	}
	result[i] = NULL;
	return (result);
}
