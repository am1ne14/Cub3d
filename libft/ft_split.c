/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 05:55:53 by mtaybi            #+#    #+#             */
/*   Updated: 2025/08/23 03:39:40 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *str, char c)
{
	size_t	word;
	size_t	f;
	size_t	i;

	word = 0;
	f = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			f = 1;
		else if (f == 1)
		{
			f = 0;
			word++;
		}
		i++;
	}
	return (word);
}

static char	*ft_strp(char const *s, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	ft_str(char **result, char const *s, char c, size_t n)
{
	size_t	i;
	size_t	len;
	size_t	index;

	i = 0;
	len = 0;
	index = 0;
	while (i < n)
	{
		while (s[index] == c)
			index++;
		len = 0;
		while (s[index + len] && s[index + len] != c)
			len++;
		result[i] = ft_strp(s + index, len);
		if (result[i] == NULL)
		{
			free_split(result);
			return (1);
		}
		index += len;
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	n;
	size_t	n_r;

	if (!s)
		return (NULL);
	n = ft_words(s, c);
	result = (char **)malloc(sizeof(char *) * (n + 1));
	if (!result)
		return (NULL);
	n_r = ft_str(result, s, c, n);
	if (n_r == 1)
		return (NULL);
	result[n] = NULL;
	return (result);
}
