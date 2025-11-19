/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:47:20 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:12:47 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	read_file(int fd, t_liste **node)
{
	t_liste	*new_node;
	int		r;

	r = 1;
	while (!newline(*node) && r > 0)
	{
		new_node = malloc(sizeof(t_liste));
		if (!new_node)
		{
			free_node(node);
			return ;
		}
		new_node->next = NULL;
		r = read(fd, new_node->content, BUFFER_SIZE);
		if ((*node == NULL && r == 0) || r == -1)
		{
			free(new_node);
			return ;
		}
		new_node->content[r] = '\0';
		if (*node == NULL)
			*node = new_node;
		else
			getlast(*node)->next = new_node;
	}
}

void	output(t_liste *node, char **line)
{
	int	len;
	int	i;
	int	j;

	if (!node)
		return ;
	len = get_line_len(node);
	*line = malloc(sizeof(char) * (len + 1));
	if (!*line)
		return ;
	i = 0;
	while (node)
	{
		j = 0;
		while (node->content[j] && node->content[j] != '\n')
			(*line)[i++] = node->content[j++];
		if (node->content[j] == '\n')
		{
			(*line)[i++] = '\n';
			break ;
		}
		node = node->next;
	}
	(*line)[i] = '\0';
}

void	free_node(t_liste **node)
{
	t_liste	*temp;

	while (*node)
	{
		temp = (*node)->next;
		free(*node);
		*node = temp;
	}
	*node = NULL;
}

char	*get_next_line(int fd)
{
	static t_liste	*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_file(fd, &node);
	if (node == NULL)
		return (NULL);
	output(node, &line);
	if (!line)
		return (free_node(&node), NULL);
	if (clean(&node) != 1)
		return (free(line), NULL);
	return (line);
}
