/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:41:07 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/05 15:33:23 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_param *p)
{
//	double	*dist;
	double	dist[p->sp_num];
	int		temp;
	int		temp_dist;
	int		i;

	i = -1;
//	dist = malloc(sizeof(double) * (p->sp_num + 1));
	printf("sprite count is %i\n", p->sp_num);
	while (++i < p->sp_num)
	{
		printf("printtaa taa %f\n", p->sprites.spr[i].x);
		dist[i] = ((p->pl.x_pos - p->sprites.spr[i].x)
				* (p->pl.x_pos - p->sprites.spr[i].x)
				+ (p->pl.y_pos - p->sprites.spr[i].y)
				* (p->pl.y_pos - p->sprites.spr[i].y));
		printf("sprite x is %f sprite y is %f\n", p->sprites.spr[i].x, p->sprites.spr[i].y);
		p->sp_order[i] = i;
		//i++;
	}
	i = 0;
	while (i < p->sp_num - 1)
	{
		printf("FIRST print this %.1f\n", dist[i]);
		printf("THEN print this %.1f\n", dist[i + 1]);
		if (dist[i] < dist[i + 1])
		{
			printf("aaa WHERE THE SEGFAULT\n");
			temp_dist = dist[i];
			dist[i] = dist[i + 1];
			dist[i + 1] = temp_dist;
			temp = p->sp_order[i];
			p->sp_order[i] = p->sp_order[i + 1];
			p->sp_order[i + 1] = temp;
			i = -1;
		}
		i++;
	}
//	free(dist);
}

void	sprite_heigth(t_param *p, t_draw_sprites *sprite)
{
	sprite->heigth = abs((int)(p->win.heigth / (sprite->y_mod)));
	sprite->y_start = -sprite->heigth / 2 + p->win.heigth / 2;
	if (sprite->y_start < 0)
		sprite->y_start = 0;
	sprite->y_end = sprite->heigth / 2 + p->win.heigth / 2;
	if (sprite->y_end >= p->win.heigth)
		sprite->y_end = p->win.heigth;
//	printf("start is %i, end is %i\n", sprite->y_start, sprite->y_end);
}

void	sprite_width(t_param *p, t_draw_sprites *sprite)
{
	sprite->width = abs((int)(p->win.heigth / (sprite->y_mod)));
//	printf("sprite width is %i\n", sprite->width);
	sprite->x_start = -sprite->width / 2 + sprite->screen;
	if (sprite->x_start < 0)
		sprite->x_start = 0;
	sprite->x_end = sprite->width / 2 + sprite->screen;
//	printf("end at this point is %i\n", sprite->x_end);
	if (sprite->x_end >= p->win.width)
		sprite->x_end = p->win.width;
//	printf("xxx start is %i, end is %i\n", sprite->x_start, sprite->x_end);
}

void	draw_sprites(t_param *p, t_draw_sprites *spr, t_text *t)
{
	int	x;
	int	y;

	x = spr->x_start;
	while (x < spr->x_end)
	{
		spr->x_text = (int)((x - (-spr->width / 2 + spr->screen))
				* t->sp_w / spr->width);
		y = spr->y_start;
		if (spr->y_mod > 0 && x >= 0 && x < p->win.width && spr->y_mod
			< (float)p->rays.buf[x])
		{
			printf("does it happen actually\n");
			while (y < spr->y_end)
			{
				spr->d = (y) * 256 - p->win.heigth * 128 + spr->heigth * 128;
				spr->y_text = ((spr->d * t->sp_h) / spr->heigth) / 256;
				if (*(t->spr + spr->x_text + spr->y_text * t->sp_sl / 4))
				{
					*(p->img.addr + spr->x + spr->y * p->img.s_len / 4)
						= *(t->spr + spr->x_text + spr->y_text * t->sp_sl / 4);
				//	my_mlx_pixel_put(p, x, y, RED);
				}
				y++;
			}
		}
		x++;
	}
}

void	sprites(t_param *p)
{
	t_draw_sprites	sprite;
	t_spr			s_ptr;
	int				i;

	printf("sprite THING is now %f\n", p->sprites.spr->x);
	printf("sprite THING is now %f\n", p->sprites.spr->y);
	sort_sprites(p);
	printf("another pointer x is %f\n", p->spr->x);
	i = 0;
	while (i < p->sp_num)
	{
		s_ptr = p->spr[p->sp_order[i]];
		i++;
		printf("sprite pointer x is %f\n", s_ptr.x);
		printf("sprite pointer y is %f\n", s_ptr.y);
		sprite.x_spr = (s_ptr.x + 0.5) - p->pl.x_pos;
		sprite.y_spr = (s_ptr.y + 0.5) - p->pl.y_pos;
		printf("sprite x is %f\n", sprite.x_spr);
		printf("sprite y is %f\n", sprite.y_spr);
		sprite.inverse = 1.0 / (p->pl.x_plane * p->pl.y_dir
				- p->pl.x_dir * p->pl.y_plane);
		printf("the inverse is %f\n", sprite.inverse);
		sprite.x_mod = sprite.inverse * (p->pl.y_dir
				* sprite.x_spr - p->pl.x_dir * sprite.y_spr);
		sprite.y_mod = sprite.inverse * (-p->pl.y_plane
				* sprite.x_spr + p->pl.x_plane * sprite.y_spr);
	//	printf("y mod is %f\n", sprite.y_mod);
	//	printf("x mod is %f\n", sprite.x_mod);
		sprite.screen = (int)((p->win.width / 2)
				* (1 + sprite.x_mod / sprite.y_mod));
	//	printf("sprite screen is %i\n", sprite.screen);
		sprite_heigth(p, &sprite);
		sprite_width(p, &sprite);
		draw_sprites(p, &sprite, &p->text);
	}
}
