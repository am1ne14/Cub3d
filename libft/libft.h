/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaybi <mtaybi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:27:31 by abousfih          #+#    #+#             */
/*   Updated: 2025/08/23 03:52:51 by mtaybi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strspn(const char *s, const char *accept);
size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strndup(const char *s, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_tolower(int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_isalnum(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_isalpha(int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isascii(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strrchr(const char *s, int c);
int		ft_isprint(int c);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strtrim(const char *s1, const char *set);
char	*get_next_line(int fd);

#endif
