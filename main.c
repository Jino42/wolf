/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:02:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/18 23:25:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlxji.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BMP_HEAD_FILE 14
#define BMP_HEAD 40

typedef struct	s_bmp
{
	short	type;
	int		file_size;
	int 	private1;
	int		offset;
	int		info_reader_size;
	int		width;
	int		height;
	short	nb_plans;
	short	bpp;
	int		compression;
	int		size_img;
	int		x_pxpmeter;
	int		y_pxpmeter;
	int		color_use;
	int		color_important;
}				t_bmp;

int			main(int argc, char **argv)
{
	void	*datas;
	t_bmp bmp;
	int fd;
	unsigned char tab[39];
	bzero(tab, 39);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (0);
	read(fd, &bmp, BMP_HEAD_FILE);
	read(fd, &bmp.info_reader_size, BMP_HEAD);
	ft_printf("%i\n", bmp.width);
//	datas = ft_memalloc(bmp.width * 4 * bmp.height);
	lseek(fd, bmp.offset, SEEK_SET);
	void *mlx = mlx_init();
	t_img *img = mlxji_new_img(mlx, 1000, 1000);
	void *win;
	win = mlx_new_window(mlx, 1000, 1000, "Wolf3d");
	int x, y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			read(fd, tab, 3);
			img->data[x * 4 + y * img->size_line] = tab[0];
			img->data[x * 4 + y * img->size_line + 1] = tab[1];
			img->data[x * 4 + y * img->size_line + 2] = tab[2];
			x++;
		}
		if (x % 4)
			read(fd, tab, x % 4);
		y++;
	}
	ft_printf("OUI\n");
	mlx_put_image_to_window(mlx, win, img->img, 0, 0);
	mlx_loop(mlx);
	close(fd);
	return (0);
}
