/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:36:21 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:41:45 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*g;

	i = 0;
	t = (unsigned char *)s1;
	g = (unsigned char *)s2;
	while (i < n)
	{
		if (t[i] != g[i])
			return (t[i] - g[i]);
		i++;
	}
	return (0);
}
