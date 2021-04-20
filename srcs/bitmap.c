/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 10:11:01 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/20 14:28:35 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *s, int n)
{
	unsigned char	*pointer;

	pointer = (unsigned char *)s;
	while (n > 0)
	{
		*pointer = 0;
		pointer++;
		n--;
	}
}

int	bitmap_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(filesize);
	header[3] = (unsigned char)(filesize >> 8);
	header[4] = (unsigned char)(filesize >> 16);
	header[5] = (unsigned char)(filesize >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(w);
	header[19] = (unsigned char)(w >> 8);
	header[20] = (unsigned char)(w >> 16);
	header[21] = (unsigned char)(w >> 24);
	header[22] = (unsigned char)(h);
	header[23] = (unsigned char)(h >> 8);
	header[24] = (unsigned char)(h >> 16);
	header[25] = (unsigned char)(h >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int	bitmap_data(int fd, t_mlx *mlx, int padsize)
{
	unsigned char	zero[3];
	int				i;
	int				j;
	int				pixel;

	j = mlx->screenh - 1;
	ft_bzero(zero, 3);
	while (j >= 0)
	{
		i = 0;
		while (i < mlx->screenw)
		{
			pixel = *(mlx->img_addr + i + j * mlx->sizeline / 4);
			write(fd, &pixel, 3);
			write(fd, &zero, padsize);
			i++;
		}
		j--;
	}
	return (1);
}

void	make_screenshot(t_all *p)
{
	int	padsize;
	int	fd;

	p->screenshot = 1;
	run_game(p);
	padsize = (4 - ((int)p->mlx->screenw * 3) % 4) % 4;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
	if (fd < 0)
		error_handling(FD, p);
	bitmap_header(fd, p->mlx->screenh, p->mlx->screenw, padsize);
	bitmap_data(fd, p->mlx, padsize);
	close(fd);
	close_game(p);
}
