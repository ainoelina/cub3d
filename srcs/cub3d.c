/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 09:49:34 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/21 11:02:42 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_screen(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->screenw, mlx->screenh);
	mlx->img_addr = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->sizeline, &mlx->endian);
}

int	run_game(t_all *p)
{
	init_screen(p->mlx);
	move(p);
	raycast(p);
	if (!p->screenshot)
	{
		mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
			p->mlx->img_ptr, 0, 0);
		mlx_destroy_image(p->mlx->mlx_ptr, p->mlx->img_ptr);
	}
	return (0);
}

void	start_game(t_all *p, char *cub, int screenshot)
{
	if (screenshot == 1)
		p->no_resizing = 1;
	p->lines = 0;
	parser(p, cub);
	p->mlx->mlx_ptr = mlx_init();
	p->screenshot = 0;
	handle_texture(p, p->txt);
	if (screenshot == 1)
		make_screenshot(p);
	p->mlx->win_ptr = mlx_new_window(p->mlx->mlx_ptr, p->mlx->screenw,
			p->mlx->screenh, "cub3d");
	mlx_hook(p->mlx->win_ptr, 2, 0, key_pressed, p);
	mlx_hook(p->mlx->win_ptr, 3, 0, key_released, p);
	mlx_hook(p->mlx->win_ptr, 17, 0, close_game, p);
	mlx_loop_hook(p->mlx->mlx_ptr, run_game, p);
	mlx_loop(p->mlx->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && cub_check(argv[1]))
		init_all(argv[1], 0);
	else if (argc == 3 && cub_check(argv[1])
		&& save_check(argv[2], "--save"))
		init_all(argv[1], 1);
	else
		printf("Error\nInvalid arguments.\n");
	return (0);
}
