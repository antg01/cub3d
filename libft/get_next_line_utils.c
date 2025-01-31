/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:45:29 by gnyssens          #+#    #+#             */
/*   Updated: 2025/01/31 01:07:56 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listt	*ft_lstneww(char *content)
{
	t_listt	*new_elem;

	if (content)
	{
		new_elem = (t_listt *)malloc(sizeof(t_listt));
		if (!new_elem)
			return (NULL);
		new_elem->content = content;
		new_elem->next = NULL;
		new_elem->len = 0;
		while (content[new_elem->len] != '\0')
			new_elem->len++;
		return (new_elem);
	}
	return (NULL);
}

void	ft_lstadd_backk(t_listt **lst, t_listt *new)
{
	t_listt	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

char	*ft_strchr_bis(t_listt *lst, int c, int loop)
{
	const char	*s;

	while (lst)
	{
		s = lst->content;
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
		if (c == '\0')
			return ((char *)s);
		lst = lst->next;
		if (!loop)
			break ;
	}
	return (NULL);
}
/*
char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = 0;
	while (s1[len])
		len++;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
*/
void	ft_strjoin_bis(char *line, t_listt *node, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (node && i < len)
	{
		tmp = node->content;
		while (*tmp && *tmp != '\n' && i < len)
			line[i++] = *tmp++;
		if (*tmp == '\n' && i < len)
			line[i++] = *tmp++;
		node = node->next;
	}
	line[i] = '\0';
}
