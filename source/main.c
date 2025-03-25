/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/25 18:27:45 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Vérifie si le fichier possède l'extension .cub.
*/
static int	check_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if (i < 5)
		return (0);
	if (filename[i - 4] != '.' || filename[i - 3] != 'c' || filename[i
         - 2] != 'u' || filename[i - 1] != 'b')
		return (0);
	return (1);
}

/*
** Vérifie le nombre d'arguments, l'extension du fichier et sa lisibilité.
*/
static int	check_arguments(int argc, char **argv)
{
	int		fd;
	char	buffer[1];
	int		ret;

	if (argc != 2)
		return (write(2, "Error: Invalid number of arguments\n", 34), 0);
	if (!check_extension(argv[1]))
		return (write(2, "Error: Invalid file extension (expected .cub)\n", 46),
			0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: Cannot open file\n", 24), 0);
	ret = read(fd, buffer, 1);
	if (ret == -1)
	{
		close(fd);
		return (write(2, "Error: File is not readable or is a directory\n", 46),
			0);
	}
	close(fd);
	return (1);
}

/*
** Point d’entrée du programme : initialise la fenêtre, vérifie les arguments
** et lance le parsing puis l'affichage du jeu.
*/
int	main(int argc, char **argv)
{
	t_mlx	data;
	int		fd;

	if (!check_arguments(argc, argv))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: Error opening file\n", 25), 1);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (write(2, "Error: mlx_init failed\n", 23), 1);
	if (!parsing(&data, fd))
		return (close(fd), write(2, "Error: Invalid map\n", 19), 1);
	handle_mlx(&data);
	return (0);
}
