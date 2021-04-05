/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:12:31 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/16 10:49:03 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** need to add valid file name check
*/

void	set_texture_path(t_param *p, char *xpm, char **texture)
{
	int		fd;

	fd = open(xpm, O_RDONLY);
	if (fd < 0)
		error_handling(TXT_INPUT, p);
	close(fd);
	*texture = xpm;
	printf("texture path now is %s\n", *texture);
}

void	set_texture(t_param *p, char *line, char **texture, int *i)
{
	int		j;
	char	*path;

	(*i) = (*i) + 2;
	if (*texture != NULL)
		error_handling(TXT_DOUBLE, p);
	while (line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	path = malloc(sizeof(char) * (*i - j + 1));
	if (!path)
		error_handling(XPM_MALLOC, p);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		path[j] = line[*i];
		j++;
		(*i)++;
	}
	path[j] = '\0';
	set_texture_path(p, path, texture);
}
