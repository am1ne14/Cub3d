/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 03:08:55 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/28 04:22:44 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t ft_strcspn(const char *str1, const char *str2)
{
    size_t count = 0;
    const char *p1 = str1;

    while (*p1 != '\0')
    {
        const char *p2 = str2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2)
                return count;
            p2++;
        }
        count++;
        p1++;
    }
    return count;
}

