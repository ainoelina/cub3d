/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 10:54:03 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/05 15:07:02 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sprites(t_param *p)
{
	int	i;
	int	j;
	int	sprites;

	i = 0;
	sprites = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '2')
				sprites++;
			j++;
		}
		i++;
	}
	return (sprites);
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
	t_spr	*sprt;
	int		pos;

	p->sp_num = count_sprites(p);
	sprt = (malloc(sizeof(t_spr) * p->sp_num));
	if (!sprt)
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
				sprt[pos].x = i;
				sprt[pos].y = j;
				pos++;
			}
			j++;
		}
		i++;
	}
	return (sprt);
}
