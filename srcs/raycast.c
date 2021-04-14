/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 14:38:31 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/14 10:36:58 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays(t_rays *ray, t_player *pl, t_all *p)
{
	pl->camera = 2 * p->stripe / (double)p->mlx->screenw - 1;
	ray->x_dir = pl->x_dir + pl->x_plane * pl->camera;
	ray->y_dir = pl->y_dir + pl->y_plane * pl->camera;
	ray->x_map = (int)(pl->x);
	ray->y_map = (int)(pl->y);
	ray->x_delta = fabs(1 / ray->x_dir);
	ray->y_delta = fabs(1 / ray->y_dir);
	ray->hit = 0;
}

void	steps(t_rays *ray, t_player *pl)
{
	if (ray->x_dir < 0)
	{
		ray->x_step = -1;
		ray->x_side = (pl->x - ray->x_map) * ray->x_delta;
	}
	else
	{
		ray->x_step = 1;
		ray->x_side = (ray->x_map + 1.0 - pl->x) * ray->x_delta;
	}
	if (ray->y_dir < 0)
	{
		ray->y_step = -1;
		ray->y_side = (pl->y - ray->y_map) * ray->y_delta;
	}
	else
	{
		ray->y_step = 1;
		ray->y_side = (ray->y_map + 1.0 - pl->y) * ray->y_delta;
	}
}

void	hits(t_map *map, t_rays *ray)
{
	while (ray->hit == 0)
	{
		if (ray->x_side < ray->y_side)
		{
			ray->x_side = ray->x_side + ray->x_delta;
			ray->x_map = ray->x_map + ray->x_step;
			ray->side = 0;
		}
		else
		{
			ray->y_side = ray->y_side + ray->y_delta;
			ray->y_map = ray->y_map + ray->y_step;
			ray->side = 1;
		}
		if (map->map[ray->x_map][ray->y_map] == '1')
			ray->hit = 1;
	}
}

void	walls(t_rays *ray, t_player *pl, t_walls *walls, t_all *p)
{
	if (ray->side == 1)
	{
		if (ray->y_map < pl->y)
			walls->direction = 'W';
		else
			walls->direction = 'E';
		ray->wall_dist = (ray->y_map - pl->y + (1 / ray->y_step)
				/ 2) / ray->y_dir;
		ray->wall = pl->x + ray->wall_dist * ray->x_dir;
	}
	else
	{
		if (ray->x_map < pl->x)
			walls->direction = 'N';
		else
			walls->direction = 'S';
		ray->wall_dist = (ray->x_map - pl->x + (1 - ray->x_step)
				/ 2) / ray->x_dir;
		ray->wall = pl->y + ray->wall_dist * ray->y_dir;
	}
	ray->buf[p->stripe] = ray->wall_dist;
}

void	raycast(t_all *p)
{
	p->stripe = 0;
	floor_ceiling(p);
	while (p->stripe < p->mlx->screenw)
	{
		init_rays(p->ray, p->pl, p);
		steps(p->ray, p->pl);
		hits(p->map, p->ray);
		walls(p->ray, p->pl, p->walls, p);
		define_walls(p->walls, p);
		define_texture(p->txt, p->walls);
		texturise(p->ray, p->walls);
		draw(p, p->walls, p->walls->start, p->walls->end);
		p->stripe++;
	}
	handle_sprites(p, p->pl, p->mlx);
}
