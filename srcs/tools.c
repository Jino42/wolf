/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:22:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/15 17:01:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		round_to_inf(float nb)
{
	return ((int)nb);
}

int		round_to_up(float nb)
{
	return ((int)nb + 1);
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	vector_rotation(float *x, float *y, float rotation)
{
	float tmp;

	tmp = *x * cos(rotation) - *y * sin(rotation);
	*y = *y * cos(rotation) + *x * sin(rotation);
	*x = tmp;
}

void	mlxji_draw_case(t_img *img, t_pxtopx *px, t_px *col)
{
	int x;
	int y;
	int dir_y;
	int dir_x;

	px->y1 < px->y2 ? (dir_y = 1) : (dir_y = -1) ;
	px->x1 < px->x2 ? (dir_x = 1) : (dir_x = -1) ;
	y = px->y1;
	while (y != px->y2)
	{
		x = px->x1;
		while (x != px->x2)
		{
			mlxji_put_pixel(img, x, y, col);
			x += dir_x;
		}
		//mlxji_put_pixel(img, x, y, col);
		y += dir_y;
	}
}
