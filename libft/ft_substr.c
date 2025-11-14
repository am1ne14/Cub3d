/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:23:50 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:37:38 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	j;

	if (!s)
		return (NULL);
	j = ft_strlen(s) - (size_t)start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len < j)
		j = len;
	dest = (char *)malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < j)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
