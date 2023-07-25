/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:41:18 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/25 17:46:48 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (p);
	ft_bzero(p, count * size);
	return (p);
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

