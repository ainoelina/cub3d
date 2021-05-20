/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 09:54:37 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/20 14:37:25 by avuorio       ########   odam.nl         */
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

int	cub_check(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c'
		&& file[i - 4] == '.')
		return (1);
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

void	check_surroundings(t_map *m, t_all *p, int x, int y)
{
	char	**map;

	p->pl->pos_check = 0;
	map = m->map;
	if (map[x][y] == ' ' && (map[x][y + 1] != '1' && map[x][y + 1] != ' '))
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2' || map[x][y] == ' ')
		&& map[x][y + 1] == '\0')
		error_handling(MAP_WALLS, p);
	if (x == 0 && (map[x][y] != '1' && map[x][y] != ' '))
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2') && y == 0)
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2') && map[x][y - 1] == ' ')
		error_handling(MAP_WALLS, p);
	if (map[x][y] == ' ' && (map[x][y + 1] == '0' || map[x][y + 1] == '2'))
		error_handling(MAP_WALLS, p);
	if (x == m->x_max - 1 && (map[x][y] != '1'))
		error_handling(MAP_WALLS, p);
}

void	check_map(t_map *map, t_all *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->x_max)
	{
		j = 0;
		while (j < map->y_max)
		{
			if (map->map[i][j] != '1' && map->map[i][j] != 'A'
			&& map->map[i][j] != '\0')
				check_surroundings(map, p, i, j);
			j++;
		}
		i++;
	}
}
