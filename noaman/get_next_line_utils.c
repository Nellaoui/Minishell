/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:46:13 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/24 16:58:14 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen2(char *s)
// {
// 	size_t	i;

// 	if (!(s))
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

char	*cline(char *s)
{
	char	*cline;
	int		i;
	int		j;

	j = 0;
	while (s[j] != '\n' && s[j] != '\0')
		j++;
	if (s[j] == '\n')
		j++;
	cline = malloc(j + 1);
	if (!cline)
		return (0);
	i = 0;
	while (i < j && s[i])
	{
		cline[i] = s[i];
		i++;
	}
	cline[i] = '\0';
	return (cline);
}

char	*bowl(char *s)
{
	int		i;
	int		j;
	char	*rest;

	if (!s)
		return (0);
	i = 0;
	if (!*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	j = 0;
	rest = (char *)malloc((ft_strlen(s) - i + 1));
	if (!rest)
		return (0);
	while (s[i])
		rest[j++] = s[i++];
	rest[j] = '\0';
	free(s);
	return (rest);
}

int	ft_strchr2(char *s, int c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!(s1))
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	s = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s)
		return (0);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	free(s1);
	return (s);
}
