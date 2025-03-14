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

long ft_strtol(const char *str, char **endptr)
{
    long result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        if (result > (LONG_MAX - (*str - '0')) / 10)
        {
            result = (sign == 1) ? LONG_MAX : LONG_MIN;
            break;
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    if (endptr)
        *endptr = (char *)str;
    return (result * sign);
}
