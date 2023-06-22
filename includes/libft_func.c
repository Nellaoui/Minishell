/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:09:18 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/22 12:58:30 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int				i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	i = 0;
// 	while (str1[i] != '\0' || str2[i] != '\0')
// 	{
// 		if (str1[i] > str2[i])
// 			return (1);
// 		else if (str1[i] < str2[i])
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strchr(const char *scanned, int searched)
// {
// 	int	i;

// 	i = 0;
// 	while (scanned[i] != (unsigned char)searched)
// 	{
// 		if (scanned[i] == '\0')
// 			return (0);
// 		i++;
// 	}
// 	return ((char *)scanned + i);
// }

// char	*ft_substr(char const *s, unsigned int start, int len)
// {
// 	char			*dest;
// 	unsigned int	l_s;
// 	int				i;

// 	if (!s)
// 		return (NULL);
// 	l_s = ft_strlen(s);
// 	if (start >= l_s)
// 		return (ft_strdup(""));
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (dest == 0)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] && len > i)
// 	{
// 		dest[i] = s[i + start];
// 		i++;
// 	}
// 	dest[len] = '\0';
// 	return (dest);
// }

// char	*ft_strdup(const char *s1)
// {
// 	int		size;
// 	char	*dup;
// 	char	*duplicate;

// 	size = ft_strlen(s1);
// 	dup = (char *)malloc(sizeof(char) * size + 1);
// 	if (!dup)
// 		return (NULL);
// 	duplicate = dup;
// 	while (*s1)
// 	{
// 		*duplicate = *s1;
// 		duplicate++;
// 		s1++;
// 	}
// 	*duplicate = '\0';
// 	return (dup);
// }

// int	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (s)
// 	{
// 		while (*s)
// 		{
// 			write(fd, s, 1);
// 			s++;
// 		}
// 	}
// }

// int	cword(char const *ptr, char cep)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	x = 0;
// 	while (ptr[i])
// 	{
// 		while (ptr[i] == cep && ptr[i])
// 			i++;
// 		if (ptr[i])
// 			x++;
// 		while (ptr[i] != cep && ptr[i])
// 			i++;
// 	}
// 	return (x);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ss;
// 	int		i;
// 	int		len;
// 	int		countage;

// 	if (!s)
// 		return (0);
// 	ss = malloc(sizeof(char *) * (cword(s, c) + 1));
// 	if (!ss)
// 		return (0);
// 	i = 0;
// 	len = 0;
// 	countage = 0;
// 	while (countage < cword(s, c))
// 	{
// 		while (s[len] == c && s[len])
// 			len++;
// 		if (s[len] && s[len] != c)
// 			i = len;
// 		while (s[len] != c && s[len])
// 			len++;
// 		ss[countage++] = ft_substr(s, i, len - i);
// 	}
// 	ss[countage] = 0;
// 	return (ss);
// }