/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:45:15 by aziyani           #+#    #+#             */
/*   Updated: 2023/07/28 16:48:12 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*next_line(char	*saver, int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	i = 1;
	while (i != 0 && !(ft_strchr2(saver, '\n')))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(saver);
			free(buffer);
			saver = 0;
			return (0);
		}
		buffer[i] = '\0';
		saver = ft_strjoin2(saver, buffer);
	}
	free(buffer);
	return (saver);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saver;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saver = next_line(saver, fd);
	if (!saver)
		return (0);
	if (saver[0] == '\0')
	{
		free(saver);
		saver = NULL;
		return (NULL);
	}
	line = cline(saver);
	saver = bowl(saver);
	return (line);
}
