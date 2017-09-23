/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:22:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/23 15:26:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			round_to_inf(float nb)
{
	return ((int)nb);
}

int			round_to_up(float nb)
{
	return ((int)nb + 1);
}

int			ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int			ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void		fvector_rotation(t_fvector2d *vec, float rotation)
{
	float tmp;

	tmp = vec->x * cos(rotation) - vec->y * sin(rotation);
	vec->y = vec->y * cos(rotation) + vec->x * sin(rotation);
	vec->x = tmp;
}

void		mlxji_draw_case(t_img *img, t_pxtopx *px, int col)
{
	int x;
	int y;
	int dir_y;
	int dir_x;

	px->y1 < px->y2 ? (dir_y = 1) :
							(dir_y = -1);
	px->x1 < px->x2 ? (dir_x = 1) :
							(dir_x = -1);
	y = px->y1;
	while (y != px->y2)
	{
		x = px->x1;
		while (x != px->x2)
		{
			mlxji_put_pixel(img, x, y, col);
			x += dir_x;
		}
		mlxji_put_pixel(img, x, y, col);
		y += dir_y;
	}
}

int			mlxji_rgb_to_int(t_px *col)
{
	return (((col->r << 16) + (col->g << 8) + col->b));
}

void		mlxji_draw_y_line(t_img *img, t_pxtopx *to, int col)
{
	int x;

	x = to->x1 << 2;
	while (to->y1 < to->y2)
	{
		*((int *)&img->data[x + to->y1 * img->size_line]) = col;
		to->y1++;
	}
}

void		mlxji_draw_x_line(t_img *img, t_pxtopx *to, t_px *px)
{
	int y;

	y = to->y1 * img->size_line;
	while (to->x1 < to->x2)
	{
		*((int *)&img->data[(to->x1 << 2) + y]) =
				((px->r << 16) + (px->g << 8) + px->b);
		to->x1++;
	}
}
