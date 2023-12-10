/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vyesilyu <Vyesilyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:39:59 by Vyesilyu          #+#    #+#             */
/*   Updated: 2023/12/10 21:03:02 by Vyesilyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffer)
{
	char	*str;
	int		bytes_read;

	bytes_read = 1;
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			free(buffer);
			return (0);
		}
		*(str + bytes_read) = '\0';
		buffer = ft_strjoin(buffer, str);
	}
	free(str);
	return (buffer);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (*buffer == '\0')
		return (NULL);
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) == '\n')
		str = malloc(i + 2);
	else
		str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*(buffer + i) && *(buffer + i) != '\n')
	{
		*(str + i) = *(buffer + i);
		i++;
	}
	if (*(buffer + i) == '\n')
		*(str + i++) = '\n';
	*(str + i) = '\0';
	return (str);
}

char	*ft_newline(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (!*(buffer + i))
	{
		free(buffer);
		return (NULL);
	}
	str = malloc(ft_strlen(buffer) - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (*(buffer + i))
		*(str + j++) = *(buffer + i++);
	*(str + j) = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_newline(buffer[fd]);
	return (line);
}
