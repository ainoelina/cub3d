/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sprite.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 10:51:08 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 17:54:24 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sprite_counter(t_map *map)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (i < map->x_max)
	{
		j = 0;
		while (j < map->y_max)
		{
			if (map->map[i][j] == '2')
				num++;
			j++;
		}
		i++;
	}
	return (num);
}

t_spr_ptr	*parse_sprites(t_all *p, int i, int j)
{
	t_spr_ptr	*sprites;
	int			pos;

	p->spritenum = sprite_counter(p->map);
	sprites = (malloc(sizeof(t_spr_ptr) * p->spritenum));
	p->spriteorder = (malloc(sizeof(int) * p->spritenum));
	pos = 0;
	while (i < p->map->x_max)
	{
		j = 0;
		while (j < p->map->y_max)
		{
			if (p->map->map[i][j] == '2')
			{
				sprites[pos].x = i;
				sprites[pos].y = j;
				pos++;
			}
			j++;
		}
		i++;
	}
	return (sprites);
}
