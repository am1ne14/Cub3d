/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:17:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/01/03 22:17:00 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static t_liste	**stash(void)
{
	static t_liste	*node;

	return (&node);
}

t_liste	**get_stash(void)
{
	return (stash());
}

void	reset_gnl_stash(void)
{
	free_node(stash());
}
