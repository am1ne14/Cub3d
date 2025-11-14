/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 05:22:58 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:41:17 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	long	h;

	h = n;
	i = len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	if (h == 0)
	{
		str[0] = '0';
	}
	if (h < 0)
	{
		str[0] = '-';
		h = -h;
	}
	while (h > 0)
	{
		str[--i] = h % 10 + '0';
		h = h / 10;
	}
	return (str);
}
