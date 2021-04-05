/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:37:38 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/08 12:30:13 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(t_param *p, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		parse_map(p, line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.n_txt, &i);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.e_txt, &i);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.s_txt, &i);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.w_txt, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_color(p, line, &p->text.floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_color(p, line, &p->text.ceiling, &i);
	return (0);
}

char	**get_array_lines(t_param *p, char **temp, int fd)
{
	char	*line;
	int		x;
	int		y;
	int		reader;

	reader = 1;
	x = 1;
	while (reader)
	{
		reader = get_next_line(fd, &line);
		temp = p->lines;
		y = 0;
		p->lines = malloc(sizeof(char *) * (x + 1));
		if (temp)
		{
			while (temp[y])
			{
				p->lines[y] = temp[y];
				y++;
			}
		}
		free(temp);
		p->lines[y + 1] = line;
		p->lines[y] = 0;
		x++;
	}
	return (p->lines);
}

int	parser(t_param *p, char *file)
{
	char	**temp;
	int		fd;
	int		reader;

	printf("\naccessing parse funcion\n\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handling(FD, p);
	p->lines = 0;
	p->lines = get_array_lines(p, temp, fd);
/*	while (reader == 1)
	{
		reader = get_next_line(fd, &line);
		if (check_line(p, line) == -1)
			reader = -1;
		free(line);
	}*/
	close(fd);
	define_position(p);
	return (1);
}
