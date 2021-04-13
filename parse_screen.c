/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_screen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 14:30:48 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/12 11:02:34 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* need to still manage resolution bigger than display */
/* need to still make input checks */

void	convert_colour(int r, int g, int b, unsigned int *colour)
{
	unsigned int	result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	*colour = result;
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
	(*i)++;
	green = my_atoi(line, i);
	(*i)++;
	blue = my_atoi(line, i);
	skip_spaces(i, line);
	if (red > 255 || green > 255 || blue > 255 || line[*i] != '\0')
		error_handling(COLOUR_INPUT, p);
	convert_colour(red, green, blue, colour);
}

void	set_resolution(t_all *p, char *line, int *i)
{
	if (p->mlx->resolution != 0)
		error_handling(RESOLUTION_DOUBLE, p);
	p->mlx->resolution = 1;
	(*i)++;
	skip_spaces(i, line);
	p->mlx->screenw = my_atoi(line, i);
	p->mlx->screenh = my_atoi(line, i);
	if (p->mlx->screenw <= 0 || p->mlx->screenh <= 0)
		error_handling(RESOLUTION_INVALID, p);
}
