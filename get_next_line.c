/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlobun <rlobun@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:18:22 by rlobun            #+#    #+#             */
/*   Updated: 2024/07/18 16:39:12 by rlobun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*acc_buff(char *res_buffer, char *read_buf)
{
	char	*aux;

	if (!res_buffer)
	{
		aux = ft_strdup(read_buf);
		free (res_buffer);
		return (aux);
	}
	aux = ft_strjoin (res_buffer, read_buf);
	free (res_buffer);
	return (aux);
}

char	*read_from_file(int fd, char *buffer)
{
	char	*buf_read;
	ssize_t	bytes_read;

	buf_read = malloc((BUFFER_SIZE) * sizeof(char));
	if (!buf_read)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf_read, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buf_read);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buf_read[bytes_read] = '\0';
		buffer = acc_buff (buffer, buf_read);
		if (ft_strchr (buf_read, '\n'))
			break ;
	}
	free (buf_read);
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(((ft_strlen(buffer) - i + 1)) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
