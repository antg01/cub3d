/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:43:49 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/29 15:26:47 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft.h"

typedef struct s_listt
{
	char			*content;
	struct s_listt	*next;
	ssize_t			len;
}					t_listt;

t_listt				*ft_lstneww(char *content);
void				ft_lstadd_backk(t_listt **lst, t_listt *new);
char				*ft_strchr_bis(t_listt *lst, int c, int loop);
char				*ft_strdup(const char *s1);
void				ft_strjoin_bis(char *line, t_listt *node, size_t len);
t_listt				**free_node(t_listt **node, int loop);
char				*get_line_from_list(t_listt *lst);
void				clean_buffer(t_listt **lst);
int					read_to_buffer(int fd, t_listt **lst);
char				*get_next_line(int fd);

#endif