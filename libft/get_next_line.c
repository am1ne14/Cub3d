/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by mtaybi            #+#    #+#             */
/*   Updated: 2025/01/14 10:00:00 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static char *ft_strjoin_gnl(char *s1, char *s2)
{
    char *result;
    int i, j;
    
    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    if (!s1 || !s2)
        return (NULL);
    
    result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';
    
    free(s1);
    return (result);
}

static char *extract_line(char *buffer)
{
    char *line;
    int i;
    
    if (!buffer || !buffer[0])
        return (NULL);
    
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    line = malloc(i + 2);
    if (!line)
        return (NULL);
    
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    line[i] = '\0';
    
    return (line);
}

static char *update_buffer(char *buffer)
{
    char *new_buffer;
    int i, j;
    
    if (!buffer)
        return (NULL);
        
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    
    new_buffer = malloc(ft_strlen(buffer) - i + 1);
    if (!new_buffer)
    {
        free(buffer);
        return (NULL);
    }
    
    i++;
    j = 0;
    while (buffer[i])
        new_buffer[j++] = buffer[i++];
    new_buffer[j] = '\0';
    
    free(buffer);
    return (new_buffer);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *temp;
    char *line;
    int bytes_read;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    temp = malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
    
    bytes_read = 1;
    while ((!buffer || !ft_strchr(buffer, '\n')) && bytes_read != 0)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(temp);
            if (buffer)
            {
                free(buffer);
                buffer = NULL;
            }
            return (NULL);
        }
        temp[bytes_read] = '\0';
        buffer = ft_strjoin_gnl(buffer, temp);
        if (!buffer)
        {
            free(temp);
            return (NULL);
        }
    }
    
    free(temp);
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    
    return (line);
}
