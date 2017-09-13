/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 22:45:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_pxtopx rotation_point(t_pxtopx to, double angle)
{
	double ret;
	int nx;
	int ny;

	ret = (angle / 180 * 3.1415);
	nx = to.x2 - to.x1;
	ny = to.y2 - to.y1;
	to.x2 = to.x1 + nx * cos(ret) - ny * sin(ret);
	to.y2 = to.y1 + ny *cos(ret) + nx * sin(ret);
	return (to);
}

static void	draw_radar(t_env *e)
{
	static int angle = 0;

	t_px col;

	col.r = 255;
	t_pxtopx px;

	px.x1 = WIN_WIDTH / 2;
	px.y1 = WIN_HEIGHT / 2;
	px.x2 = px.x1 + 100;
	px.y2 = px.y1;
	angle += 1 % 360;
	px = rotation_point(px, angle);
	mlxji_draw_line(e->img, &col, &px);
	angle++;
}

/*
** tan = sin(x) / cos(x);
*/

int			loop(t_env *e)
{
	ft_bzero(e->img->data, e->height * e->width * 4);
	draw_radar(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
