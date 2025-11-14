/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:29:31 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:39:03 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	if (size <= ld)
	{
		return (size + ls);
	}
	while (src[i] != '\0' && (ld + i) < size - 1)
	{
		dst[i + ld] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
