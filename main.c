/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:02:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/19 21:41:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlxji.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BMP_HEAD_TYPE 2
#define BMP_HEAD_FILE 12
#define BMP_HEAD 40
#define BMP_TYPE_BM 19778

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

void		read_bmp()
{
}

int			main(int argc, char **argv)
{
	int fd;
	unsigned char	*datas;
	t_bmp bmp;
	unsigned char tab[3];
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (0);
	read(fd, &bmp.type, BMP_HEAD_TYPE);
	read(fd, &bmp.file_size, BMP_HEAD_FILE);
	read(fd, &bmp.info_reader_size, BMP_HEAD);
	if (bmp.compression || bmp.bpp != 24 || bmp.type != BMP_TYPE_BM)
		return (0);
	lseek(fd, bmp.offset, SEEK_SET);
	void *mlx = mlx_init();
	t_img *img = mlxji_new_img(mlx, 1000, 1000);
	void *win;
	win = mlx_new_window(mlx, 1000, 1000, "Wolf3d");
	if (!(datas = ft_memalloc((bmp.height * bmp.width * 4))))
		exit(0);
	int x, y = bmp.height - 1;
	int lool = bmp.width * 4;
	while (y >= 0)
	{
		x = bmp.width - 1;
		while (x >= 0)
		{
			read(fd, tab, 3);
			datas[x * 4 + y * lool] = tab[0];
			datas[x * 4 + y * lool + 1] = tab[1];
			datas[x * 4 + y * lool + 2] = tab[2];
			x--;
		}
		if (bmp.width % 4)
			read(fd, tab, bmp.width % 4);
		y--;
	}
	y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			img->data[x * 4 + y * img->size_line] =
							datas[x * 4 + y * lool];
			img->data[x * 4 + y * img->size_line + 1] =
							datas[x * 4 + y * lool + 1];
			img->data[x * 4 + y * img->size_line + 2] =
							datas[x * 4 + y * lool + 2];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img->img, 0, 0);
	mlx_loop(mlx);
	close(fd);
	return (0);
}
