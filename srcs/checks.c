/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 09:54:37 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/18 15:40:24 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_input(t_all *p)
{
	if (p->txt->ceiling == -1 || p->txt->floor == -1)
		error_handling(COLOUR_MISSING, p);
	if (!p->txt->north_tex || !p->txt->east_tex || !p->txt->south_tex
		|| !p->txt->west_tex || !p->txt->spr_tex)
		error_handling(TEXTURE_MISSING, p);
	if (p->mlx->screenh == 0 || p->mlx->screenw == 0)
		error_handling(RESOLUTION_MISSING, p);
}

int	file_check(char *file, char format)
{
	int	i;

	i = 0;
	if (format == 'c')
	{
		while (file[i])
			i++;
		if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c'
			&& file[i - 4] == '.')
			return (1);
	}
	i = 0;
	if (format == 'x')
	{
		while (file[i])
			i++;
		if (file[i - 1] == 'm' && file[i - 2] == 'p' && file[i - 3] == 'x'
			&& file[i - 4] == '.')
			return (1);
	}
	return (0);
}

int	save_check(char *argv, char *save)
{
	int	i;

	i = 0;
	while (argv[i] == save[i])
	{
		if (argv[i] == '\0' && argv[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}
