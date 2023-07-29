/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:09:18 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/29 13:21:32 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *scanned, int searched)
{
	int	i;

	i = 0;
	while (scanned[i] != (unsigned char)searched)
	{
		if (scanned[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)scanned + i);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char			*dest;
	unsigned int	l_s;
	int				i;

	if (!s)
		return (NULL);
	l_s = ft_strlen(s);
	if (start >= l_s)
		return (ft_strdup(""));
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (NULL);
	i = 0;
	while (s[i] && len > i)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dup;
	char	*duplicate;

	size = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * size + 1);
	if (!dup)
		return (NULL);
	duplicate = dup;
	while (*s1)
	{
		*duplicate = *s1;
		duplicate++;
		s1++;
	}
	*duplicate = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	size_t	i;
	size_t	j;
	char	*point;

	if ((s1 == 0) || (s2 == 0))
		return (NULL);
	total = (ft_strlen(s1) + ft_strlen(s2));
	point = (char *)malloc(sizeof(char) * (total + 1));
	if (!point)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		point[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		point[i++] = s2[j++];
	point[i] = '\0';
	return (point);
}
