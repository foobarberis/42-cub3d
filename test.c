#include "mlx.h"
#include <stdio.h>
#include <stdint.h>

/* cc -Imlx_linux -fsanitize=address,undefined test.c mlx_linux/libmlx_Linux.a mlx_linux/libmlx.a -lXext -lX11 */

typedef struct s_img t_img;

struct s_img
{
	void	*img;
	int		w;
	int		h;
	char *addr;
	int   bpp;
	int   llen;
	int   end;
};

static uint32_t get_color(char *addr)
{
	uint32_t color;

	color = 0;
	color = color | addr[2];
	color = (color << 8) | addr[1];
	color = (color << 8) | addr[0];
	return (color);
}

void	mlx_pixel_put_img(char *addr, int llen, int bpp, int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * llen + (x << 2));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_img	img, tex;
	char	*addr;
	void	*win, *mlx;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "test");

	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.end);

	tex.img = mlx_xpm_file_to_image(mlx, "assets/eagle.xpm", &tex.w, &tex.h);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.llen, &tex.end);

	printf("img :: w: %d, h: %d, bpp: %d, llen: %d, end: %d\n", 800, 600, img.bpp, img.llen, img.end);
	printf("tex :: w: %d, h: %d, bpp: %d, llen: %d, end: %d\n", tex.w, tex.h, tex.bpp, tex.llen, tex.end);
	for (int y = 0; y < tex.h; y++)
		for (int x = 0; x < tex.w; x++)
		{
			// printf("%d, %d, %d\n", tex.addr[y * tex.llen + (x << 2)], tex.addr[y * tex.llen + (x << 2) + 1], tex.addr[y * tex.llen + (x << 2) + 2]);
			// mlx_pixel_put_img(img.addr, img.llen, img.bpp, x, y, tex.addr[y * tex.llen + (x << 2)]);
			mlx_pixel_put_img(img.addr, img.llen, img.bpp, x, y, get_color(tex.addr + (y * tex.llen + (x << 2))));
		}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}


/* 	for (int y = 0; y < tex.h; y++)
	{
		for (int x = 0; x < tex.w; x++)
			printf("%d, ", (int8_t)tex.addr[y * tex.llen + x * (tex.bpp / 8)]);
		printf("\n");
	} */
