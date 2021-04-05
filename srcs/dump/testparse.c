/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testparse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:40:55 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/23 12:34:06 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_param(char *line, t_param *p)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_color(p, line, &p->text.floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_color(p, line, &p->text.ceiling, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		parse_map1(p, line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.n_txt, &i);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.e_txt, &i);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.s_txt, &i);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.w_txt, &i);
	if (line[i] == 'S' && line[i + 1] == ' ')
		set_texture(p, line, &p->text.sp_txt, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	return (1);
}

void	copier(char **lines, int *j, char **temp)
{
	if (temp)
	{
		while (temp[*j])
		{
			lines[*j] = temp[*j];
			(*j)++;
		}
	}
}

char	**get_lines(char **lines, char **tmp, int fd)
{
	char	*s;
	int		i;
	int		j;
	int		ret;

	ret = 1;
	i = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		tmp = lines;
		j = 0;
		lines = malloc((i + 1) * sizeof(char *));
		copier(lines, &j, tmp);
		free(tmp);
		lines[j] = s;
		j++;
		lines[j] = 0;
		i++;
	}
	return (lines);
}

char	**parse_lines(t_param *p, char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == '\n')
			j++;
		if (!check_param(lines[i], p))
			return (&lines[i]);
		i++;
	}
	error_handling(MAP_INVALID, p);
	return (lines);
}

int		parsing(t_param *p, char *file)
{
	char 	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handling(FD, p);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (!check_param(line, p))
			ret = -1;
		free(line);
	}
	close(fd);
	return (1);
}

// int	parsing(t_param *p, char *file)
// {
// 	int		fd;
// 	char	**array;
// 	char	**map_array;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		error_handling(FD, p);
// 	array = NULL;
// 	p->lines = 0;
// 	p->lines = get_lines(p->lines, array, fd);
// 	close (fd);
// 	map_array = parse_lines(p, p->lines);
// 	printf("texture path now is %s\n", p->text.n_txt);
// 	check_input(p);
// 	parse_map1(p, p->lines);
// //	p->sprites.spr = parse_sprites(p);
// 	double d;
// 	d = p->sprites.spr->x;
// 	double l; 
// 	l = p->sprites.spr->y;
// 	printf("sprite row is %p\n", p->sprites.spr);
// //	printf("sprite col is %f\n", l);
// //	printf("sprite location %f, %f\n", p->sprites->spr.x, p->sprites->spr.y);
// 	return (1);
// }