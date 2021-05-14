/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_screen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 14:30:48 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/14 08:38:13 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_colour(int r, int g, int b, unsigned int *colour)
{
	unsigned int	result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	*colour = result;
}

void	colour_linecheck(char *line, int *i, t_all *p)
{
	while ((line[*i] >= '0' && line[*i] <= '9') || is_space(line[*i]))
		(*i)++;
	if (line[*i] != ',')
		error_handling(COLOUR_INPUT, p);
	if (line[*i] == ',')
	{
		(*i)++;
		skip_spaces(i, line);
	}
	if (!(line[*i] >= '0' && line[*i] <= '9'))
		error_handling(COLOUR_INPUT, p);
}

void	set_colour(t_all *p, char *line, unsigned int *colour, int *i)
{
	int	red;
	int	green;
	int	blue;

	if (line[*i] == 'F' && p->txt->floor != 0)
		error_handling(COLOUR_DOUBLE, p);
	if (line[*i] == 'C' && p->txt->ceiling != 0)
		error_handling(COLOUR_DOUBLE, p);
	(*i)++;
	skip_spaces(i, line);
	red = my_atoi(line, i);
	colour_linecheck(line, i, p);
	green = my_atoi(line, i);
	colour_linecheck(line, i, p);
	blue = my_atoi(line, i);
	skip_spaces(i, line);
	if (red > 255 || green > 255 || blue > 255 || line[*i] != '\0'
		|| !red || !green || !blue)
		error_handling(COLOUR_INPUT, p);
	convert_colour(red, green, blue, colour);
}

void	resizing_check(t_all *p)
{
	int		x;
	int		y;

	mlx_get_screen_size(p->mlx->mlx_ptr, &x, &y);
	if (!p->no_resizing)
	{
		if (p->mlx->screenw > x)
			p->mlx->screenw = x;
		if (p->mlx->screenh > y)
			p->mlx->screenh = y;
	}
}

void	set_resolution(t_all *p, char *line, int *i)
{
	if (p->mlx->resolution != 0)
		error_handling(RESOLUTION_DOUBLE, p);
	p->mlx->resolution = 1;
	(*i)++;
	skip_spaces(i, line);
	if (!(line[*i] >= '0' && line[*i] <= '9'))
		error_handling(RESOLUTION_INVALID, p);
	p->mlx->screenw = my_atoi(line, i);
	if (!p->mlx->screenw)
		error_handling(RESOLUTION_INVALID, p);
	p->mlx->screenh = my_atoi(line, i);
	if (!p->mlx->screenh)
		error_handling(RESOLUTION_INVALID, p);
	if (p->mlx->screenw <= 0 || p->mlx->screenh <= 0 || line[*i] != '\0')
		error_handling(RESOLUTION_INVALID, p);
}
