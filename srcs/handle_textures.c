/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:44:19 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/31 09:44:18 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** handle_textures function retrives the unsigned int pointer
** to the xpm texture and stores the pointer in the texture
** struct sent to the function xpm_to_image
*/

// void	xpm_to_image(t_param *p, unsigned int **addr, char *path)
// {
// 	void	*img;
// 	int		arr[5];

// 	img = mlx_xpm_file_to_image(p->mlx.ptr, path, &arr[0], &arr[1]);
// 	if (img == NULL)
// 		error_handling(FD, p);
// 	*addr = (unsigned int *)mlx_get_data_addr(img, &arr[2], &arr[3], &arr[4]);
// 	printf("address %p\n", *addr);
// 	free(img);
// }

// void	handle_textures(t_param *p)
// {
// 	xpm_to_image(p, &p->text.north, p->text.n_txt);
// 	xpm_to_image(p, &p->text.east, p->text.e_txt);
// 	xpm_to_image(p, &p->text.south, p->text.s_txt);
// 	xpm_to_image(p, &p->text.west, p->text.w_txt);
// 	xpm_to_image(p, &p->text.sprite, p->text.sp_txt);
// }

void	handle_textures(t_param *p)
{
	int		arr[13];

	p->text.no = mlx_xpm_file_to_image(p->mlx.ptr,
			p->text.n_txt, &arr[0], &(p->text.n_h));
	p->text.ea = mlx_xpm_file_to_image(p->mlx.ptr,
			p->text.e_txt, &arr[1], &(p->text.e_h));
	p->text.so = mlx_xpm_file_to_image(p->mlx.ptr,
			p->text.s_txt, &arr[2], &(p->text.s_h));
	p->text.we = mlx_xpm_file_to_image(p->mlx.ptr,
			p->text.w_txt, &arr[3], &(p->text.w_h));
	p->text.sp = mlx_xpm_file_to_image(p->mlx.ptr,
			p->text.sp_txt, &(p->text.sp_w), &(p->text.sp_h));
	p->text.north = (int *)mlx_get_data_addr(p->text.no,
			&arr[4], &p->text.n_sl, &arr[5]);
	p->text.east = (int *)mlx_get_data_addr(p->text.ea,
			&arr[6], &p->text.e_sl, &arr[7]);
	p->text.south = (int *)mlx_get_data_addr(p->text.so,
			&arr[8], &p->text.s_sl, &arr[9]);
	p->text.west = (int *)mlx_get_data_addr(p->text.we,
			&arr[10], &p->text.w_sl, &arr[11]);
	p->text.spr = (int *)mlx_get_data_addr(p->text.sp,
			&arr[12], &p->text.sp_sl, &arr[13]);
}

void	choose_texture(t_param *p)
{
	if (p->walls.dir == 'N')
	{
		p->text.data = p->text.north;
		p->text.sizeline = p->text.n_sl;
		p->text.heigth = p->text.n_h;
	}
	if (p->walls.dir == 'E')
	{
		p->text.data = p->text.east;
		p->text.sizeline = p->text.e_sl;
		p->text.heigth = p->text.e_h;
	}
	if (p->walls.dir == 'S')
	{
		p->text.data = p->text.south;
		p->text.sizeline = p->text.s_sl;
		p->text.heigth = p->text.s_h;
	}
	if (p->walls.dir == 'W')
	{
		p->text.data = p->text.west;
		p->text.sizeline = p->text.w_sl;
		p->text.heigth = p->text.w_h;
	}
}
