/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:18:42 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:41:21 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*d;
	unsigned char		f;

	d = (const unsigned char *)s;
	f = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (d[i] == f)
		{
			return ((void *)&d[i]);
		}
		i++;
	}
	return (NULL);
}
