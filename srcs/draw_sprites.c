/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 16:42:34 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/14 16:08:21 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_sprite(t_all *p, double *dist, int i)
{
	int	disttemp;
	int	temp;

	while (i < p->spritenum - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			disttemp = dist[i];
			dist[i] = dist[i + 1];
			dist[i + 1] = disttemp;
			temp = p->spriteorder[i];
			p->spriteorder[i] = p->spriteorder[i + 1];
			p->spriteorder[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	sort_sprites(t_all *p, t_player *pl)
{
	double	*dist;
	int		i;

	dist = malloc(sizeof(double *) * (p->spritenum + 1));
	i = 0;
	while (i < p->spritenum)
	{
		dist[i] = ((pl->x - p->spr[i].x) * (pl->x - p->spr[i].x)
				+ (pl->y - p->spr[i].y) * (pl->y - p->spr[i].y));
		p->spriteorder[i] = i;
		i++;
	}
	i = 0;
	next_sprite(p, dist, i);
	free (dist);
}

void	sprite_heigth(t_drawsprite *spr, t_all *p)
{
	spr->heigth = abs((int)(p->mlx->screenh / (spr->y_transf)));
	spr->y_start = -spr->heigth / 2 + p->mlx->screenh / 2;
	if (spr->y_start < 0)
		spr->y_start = 0;
	spr->y_end = spr->heigth / 2 + p->mlx->screenh / 2;
	if (spr->y_end >= p->mlx->screenh)
		spr->y_end = p->mlx->screenh - 1;
}

void	sprite_width(t_drawsprite *spr, t_all *p)
{
	spr->width = abs((int)(p->mlx->screenh / (spr->y_transf)));
	spr->x_start = (-1 * spr->width) / 2 + spr->scr;
	if (spr->x_start < 0)
		spr->x_start = 0;
	spr->x_end = spr->width / 2 + spr->scr;
	if (spr->x_end >= p->mlx->screenw)
		spr->x_end = p->mlx->screenw - 1;
}

void	handle_sprites(t_all *p, t_player *pl, t_mlx *mlx)
{
	int				i;
	t_spr_ptr		sp_ptr;
	t_drawsprite	spr;

	sort_sprites(p, pl);
	i = 0;
	while (i < p->spritenum)
	{
		sp_ptr = p->spr[p->spriteorder[i]];
		i++;
		spr.x_sprite = (sp_ptr.x + 0.5) - pl->x;
		spr.y_sprite = (sp_ptr.y + 0.5) - pl->y;
		spr.invdet = 1.0 / (pl->x_plane * pl->y_dir - pl->x_dir * pl->y_plane);
		spr.x_transf = spr.invdet * (pl->y_dir * spr.x_sprite
				- pl->x_dir * spr.y_sprite);
		spr.y_transf = spr.invdet * (-pl->y_plane * spr.x_sprite
				+ pl->x_plane * spr.y_sprite);
		spr.scr = (int)((mlx->screenw / 2) * (1 + spr.x_transf / spr.y_transf));
		sprite_heigth(&spr, p);
		sprite_width(&spr, p);
		draw_sprites(&spr, p->mlx, p);
	}
}
