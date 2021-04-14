/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 20:36:09 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/14 15:39:06 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** draw_sprites loops through every vertical stripe of the sprite on screen.
*/

void	draw_sprites(t_drawsprite *spr, t_mlx *mlx, t_all *p)
{
	spr->x = spr->x_start;
	while (spr->x < spr->x_end)
	{
		spr->x_text = (int)(256 * (spr->x - (-spr->width / 2 + spr->scr))
				* p->txt->spr_w / spr->width) / 256;
		if (spr->y_transf > 0 && spr->x >= 0 && spr->x < mlx->screenw
			&& spr->y_transf < (float)p->ray->buf[spr->x])
		{
			spr->y = spr->y_start;
			while (spr->y < spr->y_end)
			{
				spr->d = spr->y * 256 - mlx->screenh * 128 + spr->heigth * 128;
				spr->y_text = ((spr->d * p->txt->spr_h) / spr->heigth) / 256;
				if (*(p->txt->sprite + spr->x_text + spr->y_text
						* p->txt->spr_sl / 4))
					*(mlx->img_addr + spr->x + spr->y * mlx->sizeline / 4)
						= *(p->txt->sprite + spr->x_text + spr->y_text
							* p->txt->spr_sl / 4);
				spr->y++;
			}
		}
		spr->x++;
	}
}

void 	floor_ceiling(t_all *p)
{
	int	x;
	int	y;

	x = 0;
	while (x < p->mlx->screenw)
	{
		y = 0;
		while (y < p->mlx->screenh / 2)
		{
			p->mlx->img_addr[y * p->mlx->screenw + x] = p->txt->ceiling;
			y++;
		}
		x++;
	}
	x = 0;
	while (x < p->mlx->screenw)
	{
		y = p->mlx->screenh / 2;
		while (y < p->mlx->screenh)
		{
			p->mlx->img_addr[y * p->mlx->screenw + x] = p->txt->floor;
			y++;
		}
		x++;
	}
}

/*
** ray->wall defined where the wall is hit
** getting x coordinate of texture (walls->texture)
*/

void	texturise(t_rays *ray, t_walls *walls)
{
	ray->wall = ray->wall - floor(ray->wall);
	walls->texture = ray->wall * (walls->sl / 4);
	if (ray->side == 0 && ray->x_dir > 0)
		walls->texture = (walls->sl / 4) - walls->texture - 1;
	else if (ray->side == 1 && ray->y_dir < 0)
		walls->texture = (walls->sl / 4) - walls->texture - 1;
}

/*
** calculating height of the line drawn on screen
** calculating lowest and highest pixel to fill on stripe
*/

void	define_walls(t_walls *walls, t_all *p)
{
	walls->line_h = (int)(p->mlx->screenh / p->ray->wall_dist);
	walls->start = -walls->line_h / 2 + p->mlx->screenh / 2;
	if (walls->start < 0)
		walls->start = 0;
	walls->end = walls->line_h / 2 + p->mlx->screenh / 2;
	if (walls->end >= p->mlx->screenh)
		walls->end = p->mlx->screenh - 1;
}

// void	draw_stripe(t_walls *walls, t_mlx *mlx, t_all *p, int stripe)
// {
// 	double	step;
// 	double	pos;
// 	int		i;
// 	int		*text;

// 	i = 0;
// 	step = 1.0 * walls->heigth / walls->line_h;
// 	pos = (walls->start - p->mlx->screenh / 2 + walls->line_h / 2) * step;
// 	text = walls->text;
// 	while (i < walls->start)
// 	{
// 		*(mlx->img_addr + stripe + i * mlx->sizeline / 4) = p->txt->ceiling;
// 		i++;
// 	}
// 	while (i <= walls->end)
// 	{
// 		*(mlx->img_addr + stripe + i + mlx->sizeline / 4) = *(text
// 			+ walls->texture + (int)pos * walls->sl / 4);
// 		pos = pos + step;
// 		i++;
// 	}
// 	while (i < mlx->screenh)
// 	{
// 		*(mlx->img_addr + stripe + i * mlx->sizeline / 4) = p->txt->floor;
// 		i++;
// 	}
// }

/*
** step counts how much to increase the texture coordinate
** per screen pixel. variable pos tracks texture coordinate.
** texture coordinate is casted to integer y (heigth - 1 is
** protect for overflow). the color byte shift makes y-side
** walls a bit darker.
*/

void	draw(t_all *p, t_walls *walls, int start, int end)
{
	long int	color;
	double		pos;
	double		step;
	int			y;

	step = 1.0 * walls->heigth / walls->line_h;
	pos = (walls->start - p->mlx->screenh / 2 + walls->line_h / 2) * step;
	color = 0;
	while (start < end)
	{
		y = (int)pos & (p->walls->heigth - 1);
		pos = pos + step;
		color = walls->text[walls->heigth * y + walls->texture];
		if (p->ray->side == 1)
			color = (color >> 1) & 8355711;
		p->mlx->img_addr[start * p->mlx->screenw + p->stripe] = color;
		start++;
	}
}
