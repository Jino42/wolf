/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:02:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/20 22:42:59 by ntoniolo         ###   ########.fr       */
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

void		read_bmp(t_bmp bmp, int fd, unsigned char *datas)
{
	unsigned char tab[3];
	int x;
	int y;
	int width_pixel;

	width_pixel = bmp.width * 4;
	y = bmp.height - 1;
	while (y >= 0)
	{
		x = bmp.width - 1;
		while (x >= 0)
		{
			read(fd, tab, 3);
			datas[x * 4 + y * width_pixel] = tab[0];
			datas[x * 4 + y * width_pixel + 1] = tab[1];
			datas[x * 4 + y * width_pixel + 2] = tab[2];
			x--;
		}
		if (bmp.width % 4)
			read(fd, tab, bmp.width % 4);
		y--;
	}
}

int			set_bmp(t_bmp *bmp, int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (!*fd)
		return (0);
	read(*fd, &bmp->type, BMP_HEAD_TYPE);
	read(*fd, &bmp->file_size, BMP_HEAD_FILE);
	read(*fd, &bmp->info_reader_size, BMP_HEAD);
	if (bmp->compression || bmp->bpp != 24 || bmp->type != BMP_TYPE_BM)
		return (0);
	lseek(*fd, bmp->offset, SEEK_SET);
	return (1);
}

int			write_img(unsigned char *datas, char *file_out, size_t size)
{
	int	fd_out;

	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC);
	if (!fd_out)
		return (ft_ret_error("Erreur sur le fichier de sortie\n"));
	write(fd_out, datas, size);
	close(fd_out);
	return (1);
}

int			main(int argc, char **argv)
{
	int fd;
	unsigned char	*datas;
	t_bmp bmp;

/*	
	   fd = open(argv[1], O_RDONLY);
	   if (!(fd))
	   return (0);
	   void *mlx = mlx_init();
	   t_img *img = mlxji_new_img(mlx, 2000, 1500);
	   void *win;
	   win = mlx_new_window(mlx, 2000, 1500, "Wolf3d");
	   int x, y;
	   unsigned char tab[4];
	   y = 0;
	   while (y < 1200) //362)
	   {
	   x = 0;
	   while (x < 1920)//644)
	   {
		   read(fd, tab, 4);
		   img->data[x * 4 + y * img->size_line] = tab[0];
		   img->data[x * 4 + y * img->size_line + 1] = tab[1];
		   img->data[x * 4 + y * img->size_line + 2] = tab[2];
		   x++;
	   }
	   y++;
	   }
	   mlx_put_image_to_window(mlx, win, img->img, 0, 0);
	   mlx_loop(mlx);
*/	   
	if (argc != 3)
		return (ft_ret_error("Nombre d'arguments incorrects"));
	if (!(set_bmp(&bmp, &fd, argv[1])))
		ft_ret_error(("Erreur sur le BMP !\n"));
	if (!(datas = ft_memalloc((bmp.height * bmp.width * 4))))
		exit(0);
	read_bmp(bmp, fd, datas);
	close(fd);
	write_img(datas, argv[2], bmp.width * bmp.height * 4);
	free(datas);
	return (0);
}
