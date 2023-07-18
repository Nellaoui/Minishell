/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:09:18 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/18 10:34:49 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
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


int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p;

	p = str;
	while (n--)
		*p++ = (unsigned char)c;
	return (str);
}

void	*ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (p);
	ft_bzero(p, count * size);
	return (p);
}

static int	counter(const char *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			n++;
		}
	}
	return (n);
}

static int	w_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		j;
	int		k;

	dest = (char **)ft_calloc((counter(s, c) + 1), (sizeof(char *)));
	if (!dest)
		return (0);
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			dest[j] = (char *)malloc((w_len(s, c) + 1) * (sizeof(char)));
			if (!dest[j])
				return (0);
			k = 0;
			while (*s && *s != c)
				dest[j][k++] = *s++;
			dest[j++][k] = '\0';
		}
	}
	dest[j] = 0;
	return (dest);
}

int	ft_isalnum(int n)
{
	if ((n >= '0' && n <= '9') || (n >= 'a' && n <= 'z') || (n >= 'A'
			&& n <= 'Z'))
		return (1);
	else
		return (0);
}
