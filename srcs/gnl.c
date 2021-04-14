/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 13:28:24 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/12 13:12:25 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*create_rest(char *rest)
{
	char	*remain;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (rest == NULL)
		return (NULL);
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (rest[i] == 0)
		return (null_return(rest));
	remain = malloc(sizeof(char) * ((str_len(rest) - i) + 1));
	if (!remain)
		return (0);
	i++;
	while (rest[i] != '\0')
	{
		remain[j] = rest[i];
		j++;
		i++;
	}
	remain[j] = '\0';
	free(rest);
	return (remain);
}

static char	*create_line(char *string)
{
	char	*line;
	size_t	i;

	if (string == NULL)
		return (NULL);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	contains_newline(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	return_value(int reader)
{
	if (reader == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest;
	char		*buffer;
	int			reader;

	reader = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!contains_newline(rest) && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
			return (minus_return(buffer));
		buffer[reader] = '\0';
		rest = join_strings(rest, buffer);
		if (!rest)
			return (-1);
	}
	free(buffer);
	*line = create_line(rest);
	rest = create_rest(rest);
	return (return_value(reader));
}
