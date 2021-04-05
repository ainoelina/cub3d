/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_win.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:42:26 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/29 10:05:34 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_color(int r, int g, int b, unsigned int *color)
{
	unsigned int	result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	*color = result;
}

void	check_color_input(char *line, t_param *p)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!(line[j] == 'F' || line[j] == 'C' || line[j] == ' '
				|| line[j] == ',' || (line[j] >= '0' && line[j] <= '9')))
			error_handling(RGB_STRING, p);
		j++;
	}
}

void	set_color(t_param *p, char *line, unsigned int *color, int *i)
{
	int	red;
	int	green;
	int	blue;

	if (line[*i] == 'F' && p->text.floor != 0)
		error_handling(COLOR_DOUBLE, p);
	if (line[*i] == 'C' && p->text.ceiling != 0)
		error_handling(COLOR_DOUBLE, p);
	check_color_input(line, p);
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	red = my_atoi(line, i);
	(*i)++;
	green = my_atoi(line, i);
	(*i)++;
	blue = my_atoi(line, i);
	while (line[*i] == ' ')
		(*i)++;
	if (red > 255 || green > 255 || blue > 255 || line[*i] != '\0')
		error_handling(COLOR_INPUT, p);
	convert_color(red, green, blue, color);
	printf("color is now %x\n", *color);
}

void	check_resolution_input(char *line, t_param *p)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!(line[j] == 'R' || line[j] == ' '
				|| (line[j] >= '0' && line[j] <= '9')))
			error_handling(RES_INVALID, p);
		j++;
	}
}

void	get_resolution(t_param *p, char *line, int *i)
{
	if (p->win.res_check)
		error_handling(RES_DOUBLE, p);
	p->win.res_check = 1;
	check_resolution_input(line, p);
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	p->win.width = my_atoi(line, i);
	p->win.heigth = my_atoi(line, i);
	if (p->win.width <= 0 || p->win.heigth <= 0)
		error_handling(RES_INVALID, p);
	printf("width is %i, heigth is %i\n", p->win.width, p->win.heigth);
	if (p->win.width > 1440)
		p->win.width = 1440;
	if (p->win.heigth > 2560)
		p->win.heigth = 2560;
}
