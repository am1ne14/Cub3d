/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-20 17:44:39 by bamdjar           #+#    #+#             */
/*   Updated: 2025/01/07 22:14:23 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	clean(t_liste **node)
{
	t_liste	*last;
	t_liste	*new_first;
	int		i;
	int		j;

	last = getlast(*node);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	new_first = malloc(sizeof(t_liste));
	if (!new_first)
		return (free_node(node), -1);
	new_first->next = NULL;
	j = 0;
	while (last->content[i])
		new_first->content[j++] = last->content[i++];
	new_first->content[j] = '\0';
	finito(j, node, new_first);
	return (1);
}

void	finito(int j, t_liste **node, t_liste *new_first)
{
	free_node(node);
	if (j == 0)
	{
		free(new_first);
		*node = NULL;
	}
	else
		*node = new_first;
}

t_liste	*getlast(t_liste *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

int	newline(t_liste *node)
{
	t_liste	*current;
	int		i;

	if (!node)
		return (0);
	current = getlast(node);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_line_len(t_liste *node)
{
	int	i;
	int	len;

	if (!node)
		return (0);
	len = 0;
	while (node)
	{
		i = 0;
		while (node->content[i])
		{
			if (node->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		node = node->next;
	}
	return (len);
}
