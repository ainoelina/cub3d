#include "mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
}				t_mlx;

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char    *dst;

    dst = mlx->addr + (y * mlx->linelen + x * (mlx->bpp / 8));
    *(unsigned int*)dst = color;
}

unsigned int	color(unsigned char r, unsigned char g, unsigned char b)
{
		unsigned int	result;

		result = 0;
		result = result + r;
		result <<= 8;
		result = result + g;
		result <<= 8;
		result = result + b;
		return (result);
}

void	fill(t_mlx *mlx, unsigned char b)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_pixel_put(mlx, x, y, color(y, x, b));
			x++;
		}
		y++;
	}
}

int	close_window(int keycode, t_mlx *p)
{
	if (keycode == 53)
	{	mlx_destroy_image(p->mlx_ptr, p->img);
		exit(0);
	}
	return (0);
}

int main(void)
{
	t_mlx mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx_ptr, 800, 480, "my first window");
	mlx.img = mlx_new_image(mlx.mlx_ptr, 800, 480);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.linelen, &mlx.endian);
//	unsigned char b = 0;
//	while (1)
//	{
//		fill(&mlx, b);
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.window, mlx.img, 0, 0);
//		usleep(500 * 1000);
//		b++;
//	}
	mlx_hook(mlx.window, 2, 1L<<0, &close_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}