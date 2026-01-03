/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 03:16:09 by bamdjar           #+#    #+#             */
/*   Updated: 2025/11/19 23:16:54 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

typedef struct s_liste
{
	char			content[BUFFER_SIZE];
	struct s_liste	*next;
}					t_liste;

char				*get_next_line(int fd);
void				read_file(int fd, t_liste **node);
void				output(t_liste *node, char **line);
int					clean(t_liste **node);
t_liste				*getlast(t_liste *node);
int					newline(t_liste *node);
int					get_line_len(t_liste *node);
void				free_node(t_liste **node);
void				finito(int j, t_liste **node, t_liste *new_first);
t_liste				**get_stash(void);
void				reset_gnl_stash(void);
#endif
