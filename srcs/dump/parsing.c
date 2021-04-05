/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:37:38 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/29 11:21:36 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_all(t_param *p)
{
	printf("camera value is %f\n", p->pl.camera);
	printf("x ray is %f\n", p->rays.x_ray);
	printf("y ray is %f\n", p->rays.y_ray);
	printf("delta distance x is %f\n", p->rays.x_delta);
	printf("delta distance y is %f\n", p->rays.y_delta);
	printf("rays hit is %i\n", p->rays.hit);
	printf("rays x step is %i\n", p->rays.x_step);
	printf("rays y step is %i\n", p->rays.y_step);
//	printf("rays x side is %f\n", p->rays.x_side);
//	printf("rays y side is %f\n", p->rays.y_side);
}

int	check_line(t_param *p, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_color(p, line, &p->text.floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_color(p, line, &p->text.ceiling, &i);
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
	return (0);
}

int	parser(t_param *p, char *file)
{
	char	*line;
	int		fd;
	int		reader;

	printf("\naccessing parse funcion\n\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handling(FD, p);
	reader = 1;
	while (reader == 1)
	{
		reader = get_next_line(fd, &line);
		if (check_line(p, line) == -1)
			reader = -1;
		free(line);
	}
	close(fd);
	define_position(p);
	return (1);
}
