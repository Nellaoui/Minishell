/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:11:00 by nelallao          #+#    #+#             */
/*   Updated: 2023/07/27 11:20:33 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (0);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

static int	niggative(int *n)
{
	if (*n < 0)
	{
		*n = *n * (-1);
		return (1);
	}
	return (0);
}

static int	ft_counter(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}


void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (0);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		minus;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	minus = niggative(&n);
	len = ft_counter(n) + minus;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	while (len--)
	{
		dest[len] = n % 10 + '0';
		n = n / 10;
	}
	if (minus)
		dest[0] = '-';
	return (dest);
}

static int	found(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		length;
	char	*dest;
	size_t	i;

	if (s1 == 0)
		return (NULL);
	length = ft_strlen(s1);
	i = 0;
	while (found(s1[i], (char *)set))
		i++;
	if (!s1[i])
		return (ft_strdup(""));
	while (found(s1[length - 1], (char *)set))
		length--;
	dest = (char *)malloc(sizeof(char) * ((length - i) + 1));
	if (!dest)
		return (NULL);
	ft_memmove(dest, &s1[i], length - i);
	dest[length - i] = '\0';
	return (dest);
}

