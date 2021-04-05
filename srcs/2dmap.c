/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2dmap.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 13:17:04 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/23 11:51:19 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// void	print_map(t_param *p)
// {
// 	int	j;
// 	int i;

// 	printf("where is iiiit\n");
// 	i = 0;
// 	j = 0;
// 	while (i < p->world.max_row)
// 	{
// 		printf("why though\n");
// 		while (j < p->world.max_col)
// 		{
// 			printf("%c", p->world.map[i][j]);
// 			j++;
// 		}
// 		printf("map line is %s\n", p->world.map[i]);
// 		i++;
// 	}
// }

void my_mlx_pixel_put(t_param *p, int x, int y, unsigned int color)
{
	int    *dst;

    dst = p->img.addr + (y * p->img.s_len + x * (p->img.bpp / 8));
    *(unsigned int*)dst = color;
}

void fill(t_param *p)
{
	int i = 0;
	int j = 0;

	while (i < p->world.max_row)
	{
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '1')
				my_mlx_pixel_put(p, j, i, WHITE);
			if (p->world.map[i][j] == '0')
				my_mlx_pixel_put(p, j, i, YELLOW);
			if (p->world.map[i][j] == 'N')
				my_mlx_pixel_put(p, j, i, RED);
			if (p->world.map[i][j] == 'E')
				my_mlx_pixel_put(p, j, i, BLUE);
			if (p->world.map[i][j] == 'S')
				my_mlx_pixel_put(p, j, i, CYAN);
			if (p->world.map[i][j] == 'W')
				my_mlx_pixel_put(p, j, i, GREEN);
			if (p->world.map[i][j] == '2')
				my_mlx_pixel_put(p, j, i, MAGENTA);

			j++;
		}
		j = 0;
		i++;
	}
}