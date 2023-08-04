/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:38:47 by nelallao          #+#    #+#             */
/*   Updated: 2022/10/20 22:59:46 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
s1: The Total string.
s2: The suffix string.
*/
#include "libft.h"

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
