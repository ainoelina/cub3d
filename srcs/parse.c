/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:28:06 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/05 10:39:33 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** parser functions read .cub file into 2-dimensional array.
** check_params function checks line by line if it contains
** necessary element. all the elements are handled in separate
** functions depending on the element identifier.
** the map and sprites within map are parsed last.
*/

int	check_params(char *line, t_all *p)
{
	int	i;

	i = 0;
	skip_spaces(&i, line);
	if (line[i] == 'R' && line[i + 1] == ' ')
		set_resolution(p, line, &i);
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_colour(p, line, &p->txt->floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_colour(p, line, &p->txt->ceiling, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->txt->north_tex, &i);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		set_texture(p, line, &p->txt->east_tex, &i);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->txt->south_tex, &i);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		set_texture(p, line, &p->txt->west_tex, &i);
	if (line[i] == 'S' && line[i + 1] == ' ')
		set_texture(p, line, &p->txt->spr_tex, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		return (0);
	return (1);
}

char	**parse_lines(t_all *p, char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (!check_params(lines[i], p))
			return (&lines[i]);
		i++;
	}
	error_handling(NO_MAP, p);
	return (lines);
}

char	**get_lines(char **lines, char **save, int fd, t_all *p)
{
	char	*line;
	int		i;
	int		k;
	int		reader;

	reader = 1;
	i = 1;
	while (reader)
	{
		reader = get_next_line(fd, &line);
		save = lines;
		k = 0;
		lines = malloc(sizeof(char *) * (i + 1));
		if (!lines)
			error_handling(MALLOC_FAIL, p);
		copy_lines(lines, &k, save);
		free(save);
		lines[k] = line;
		k++;
		lines[k] = 0;
		i++;
	}
	return (lines);
}

void	parser(t_all *p, char *cub)
{
	int		fd;
	char	**save;
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fd = open(cub, O_RDONLY);
	if (fd < 0)
		error_handling(FD, p);
	save = NULL;
	p->lines = get_lines(p->lines, save, fd, p);
	close (fd);
	array = parse_lines(p, p->lines);
	parse_map(p, array);
	p->spr = parse_sprites(p, i, j);
	free_lines(p);
}

	// printf("sprite location is %f, %f\n", p->spr->x, p->spr->y);
	// printf("north: %s,\neast: %s,\nsouth: %s,\nwest: %s.\nsprite: %s.\n",
	// 	p->txt->north_tex, p->txt->east_tex, p->txt->south_tex,
	// 	p->txt->west_tex, p->txt->spr_tex);
	// printf("resolution is now %i x %i\n", p->mlx->screenw, p->mlx->screenh);
	// printf("floor color is %x, ceiling is %x\n", p->txt->floor, p->txt->ceiling);
	// printf("player position is now x: %.1f y: %.1f\n", p->pl->x, p->pl->y);
