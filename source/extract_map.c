/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:09:01 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/26 14:26:15 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initialise l'état utilisé pour extraire et analyser la map
** depuis la liste chaînée.
*/
static void	init_extract_map_state(t_extract_state *state, t_maplist *head)
{
	state->line = NULL;
	state->started = 0;
	state->check_nsew = 0;
	state->curr = head;
}

/*
** Parcourt le fichier ligne par ligne pour extraire la map,
	vérifier sa validité
** et stocker chaque ligne dans une liste chaînée.
*/
static void	extract_map_lines(t_mlx *data, int fd, t_extract_state *state,
		int *count_rows)
{
	while (1)
	{
		state->line = get_next_line(fd);
		if (!state->line)
			break ;
		if (state->started && (*state->line == '\n' || *state->line == '\0'
				|| is_only_spaces(state->line)))
		{
			free(state->line);
			break ;
		}
		if (!state->started && (*state->line == '\n' || *state->line == '\0'
				|| is_only_spaces(state->line)))
		{
			free(state->line);
			continue ;
		}
		state->started = 1;
		check_chars(data, state->line, &state->check_nsew);
		(*count_rows)++;
		state->curr->line = state->line;
		state->curr->next = safe_malloc(sizeof(t_maplist));
		state->curr = state->curr->next;
	}
}

/*
** Parcourt le fichier ligne par ligne pour verifier
** si il y a une 2eme description de map
*/
static void	check_double_map_description(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_only_spaces(line))
		{
			free(line);
			my_exit("Error: multiple map descriptions found");
		}
		free(line);
	}
}

/*
** Parcourt le fichier ligne par ligne pour verifier
** si il y a une 2eme description de map
*/
static void	extract_map_loop(t_mlx *data, int fd, t_extract_state *state,
		int *count_rows)
{
	extract_map_lines(data, fd, state, count_rows);
	check_double_map_description(fd);
}

/*
** Extrait la map depuis le fichier, la stocke dans une liste chaînée
** et vérifie la présence d'une position de départ pour le joueur.
*/
t_maplist	*extract_map(t_mlx *data, int fd, int *count_rows)
{
	t_maplist		*head;
	t_maplist		*last;
	t_extract_state	state;

	head = safe_malloc(sizeof(t_maplist));
	init_extract_map_state(&state, head);
	extract_map_loop(data, fd, &state, count_rows);
	if (state.check_nsew == 0)
		my_exit("Error: no player start position found in map");
	last = head;
	while (last->next && last->next->line != NULL)
		last = last->next;
	if (last->next)
	{
		free(last->next);
		last->next = NULL;
	}
	return (head);
}

// static void	extract_map_loop(t_mlx *data, int fd, t_extract_state *state,
// 		int *count_rows)
// {
// 	while (1)
// 	{
// 		state->line = get_next_line(fd);
// 		if (!state->line)
// 			break ;
// 		if (state->started && (*state->line == '\n' || *state->line == '\0'
// 				|| is_only_spaces(state->line)))
// 		{
// 			free(state->line);
// 			break ;
// 		}
// 		if (!state->started && (*state->line == '\n' || *state->line == '\0'
// 				|| is_only_spaces(state->line)))
// 		{
// 			free(state->line);
// 			continue ;
// 		}
// 		state->started = 1;
// 		check_chars(data, state->line, &state->check_nsew);
// 		(*count_rows)++;
// 		state->curr->line = state->line;
// 		state->curr->next = safe_malloc(sizeof(t_maplist));
// 		state->curr = state->curr->next;
// 	}
// }
