/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 10:54:03 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/05 10:14:17 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sprites(t_param *p)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '2')
			{
				printf("map line %s\n", p->world.map[i]);
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	malloc_sprites(t_param *p, t_spr *sprites)
{
	sprites = malloc(sizeof(t_spr) * p->sp_num);
	if (!sprites)
		error_handling(SPRITE_MALLOC, p);
	p->sp_order = malloc(sizeof(int) * p->sp_num);
	if (!p->sp_order)
		error_handling(SPRITE_MALLOC, p);
}

t_spr	*parse_sprites(t_param *p)
{
	int		i;
	int		j;
	t_spr	*ptr_sprite;
	int		pos;

	p->sp_num = count_sprites(p);
	ptr_sprite = (malloc(sizeof(t_spr) * p->sp_num));
	if (!ptr_sprite)
		error_handling(SPRITE_MALLOC, p);
	p->sp_order = (malloc(sizeof(int) * p->sp_num));
	if (!p->sp_order)
		error_handling(SPRITE_MALLOC, p);
//	malloc_sprites(p, ptr_sprite);
	i = 0;
	pos = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '2')
			{
				ptr_sprite[pos].x = i;
				ptr_sprite[pos].y = j;
				pos++;
			}
			j++;
		}
		i++;
	}
	return (ptr_sprite);
}
