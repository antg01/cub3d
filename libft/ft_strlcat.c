/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:26:42 by gnyssens          #+#    #+#             */
/*   Updated: 2024/04/22 13:10:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + src_len);
	i = 0;
	while (i < size - dest_len - 1 && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (*dest)
		dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
/*
int main(void)
{
	char	first[40] = "partie 1___";
	char	sec[] = "partie 2";

	int longueur = ft_strlcat(first, sec, 20);
	printf("%s\n", first);

	return (0);
}
*/
