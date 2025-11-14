/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:41:08 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:39:19 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	new = malloc((sizeof(char) * i + 1));
	if (!new)
		return (NULL);
	while (s[j])
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}
