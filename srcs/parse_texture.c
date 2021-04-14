/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 14:10:23 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 17:51:38 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_texture(t_all *p, t_texture *txt)
{
	int		arr[14];

	txt->northptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
			txt->north_tex, &arr[0], &(txt->north_h));
	txt->eastptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
			txt->east_tex, &arr[1], &(txt->east_h));
	txt->southptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
			txt->south_tex, &arr[2], &(txt->south_h));
	txt->westptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
			txt->west_tex, &arr[3], &(txt->west_h));
	txt->sprptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
			txt->spr_tex, &(txt->spr_w), &(txt->spr_h));
	txt->north = (int *)mlx_get_data_addr(txt->northptr,
			&arr[4], &(txt->north_sl), &arr[5]);
	txt->east = (int *)mlx_get_data_addr(txt->eastptr,
			&arr[6], &(txt->east_sl), &arr[7]);
	txt->south = (int *)mlx_get_data_addr(txt->southptr,
			&arr[8], &(txt->south_sl), &arr[9]);
	txt->west = (int *)mlx_get_data_addr(txt->westptr,
			&arr[10], &(txt->west_sl), &arr[11]);
	txt->sprite = (int *)mlx_get_data_addr(txt->sprptr,
			&arr[12], &(txt->spr_sl), &arr[13]);
}

void	define_texture(t_texture *txt, t_walls *walls)
{
	if (walls->direction == 'N')
	{
		walls->text = txt->north;
		walls->sl = txt->north_sl;
		walls->heigth = txt->north_h;
	}
	else if (walls->direction == 'E')
	{
		walls->text = txt->east;
		walls->sl = txt->east_sl;
		walls->heigth = txt->east_h;
	}
	else if (walls->direction == 'S')
	{
		walls->text = txt->south;
		walls->sl = txt->south_sl;
		walls->heigth = txt->south_h;
	}
	else if (walls->direction == 'W')
	{
		walls->text = txt->west;
		walls->sl = txt->west_sl;
		walls->heigth = txt->west_h;
	}
}

void	set_texture_path(t_all *p, char *xpm, char **texture)
{
	int		fd;

	fd = open(xpm, O_RDONLY);
	if (fd < 0)
		error_handling(FD, p);
	close(fd);
	*texture = xpm;
}

void	set_texture(t_all *p, char *line, char **texture, int *i)
{
	int		j;
	char	*path;

	(*i) = (*i) + 2;
	if (*texture != NULL)
		error_handling(TEXTURE_DOUBLE, p);
	while (line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	path = malloc(sizeof(char) * (*i - j + 1));
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		path[j] = line[*i];
		j++;
		(*i)++;
	}
	path[j] = '\0';
	set_texture_path(p, path, texture);
}
