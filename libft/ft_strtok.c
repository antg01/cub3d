/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:48:19 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/15 20:00:32 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *saved;
    char *token;

    if (str)
        saved = str;
    if (!saved || *saved == '\0')
        return (NULL);

    while (*saved && strchr(delim, *saved))
        saved++;
    if (*saved == '\0')
        return (NULL);

    token = saved;
    while (*saved && !strchr(delim, *saved))
        saved++;

    if (*saved)
    {
        *saved = '\0';
        saved++;
    }
    return (token);
}
