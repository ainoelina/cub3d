/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 09:54:37 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/14 14:04:04 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_input(t_all *p)
{
	if (p->txt->ceiling == 0 || p->txt->floor == 0)
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

void	map_check(t_all *p, t_map *m, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->x_max)
	{
		j = 0;
		while (j < m->y_max)
		{
			while (map[i][j] == ' ')
				j++;
			if ((i == 0 && map[i][j] != '1') || (i == m->x_max
				&& (map[i][j] != '1' || map[i][j] != 'A')) || (j == 0 && map[i][j] != '1')
				|| (j == m->y_max && (map[i][j] != '1' || map[i][j] != 'A'))
				|| (map[i][j] == 'A' && map[i][j - 1] == '0'))
				{ printf("max x is %i, max y is %i\n", p->map->x_max, p->map->y_max);
					printf("invalid char is '%c'\ncoordinates are %i, %i\n", map[i][j], i, j);
				error_handling(MAP_INVALID, p); }
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2' && map[i][j] != 'A'
				&& map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'W')
				error_handling(MAP_INVALID, p);
			j++;
		}
		i++;
	}
}

// void	checkmap(t_all *p, int x, int y)
// {
// 	char	**map;

// 	p->pl->pos_check = 0;
// 	map = p->map->map;
// 	if (map[x][y] == '1' || map[x][y] == 'O' || map[x][y] == 'X')
// 		return ;
// 	if (x == 0 || y == 0 || x == p->map->x_max)
// 		error_handling(MAP_INVALID, p);
// 	if (map[x][y] == 'A')
// 		error_handling(MAP_INVALID, p);
// 	if (map[x][y] == '0')
// 		map[x][y] = 'O';
// 	if (map[x][y] == '2')
// 		map[x][y] = 'X';
// 	checkmap(p, x + 1, y);
// 	checkmap(p, x, y + 1);
// 	checkmap(p, x - 1, y);
// 	checkmap(p, x, y - 1);
// }

// int	check_map(t_all *p)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (i < p->map->x_max)
// 	{
// 		j = 0;
// 		while (j < p->map->y_max)
// 		{
// 			if (p->map->map[i][j] != '1' && i == 0)
// 				return (-1);
// 			else if (p->map->map[i][j] != '1' && i == p->map->x_max - 1)
// 				return (-1);
// 			else if (p->map->map[i][j] != '1' && j == 0)
// 				return (-1);
// 			else if (p->map->map[i][j] != '1' && j == p->map->y_max - 1)
// 				return (-1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }
