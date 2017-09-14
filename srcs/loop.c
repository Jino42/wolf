/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/13 23:24:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_pxtopx rotation_point(t_pxtopx to, float angle)
{
	float ret;
	int nx;
	int ny;

	ret = angle;
	nx = to.x2 - to.x1;
	ny = to.y2 - to.y1;
	to.x2 = to.x1 + nx * cos(ret) - ny * sin(ret);
	to.y2 = to.y1 + ny *cos(ret) + nx * sin(ret);
	return (to);
}

static void	draw_radar(t_env *e)
{
	t_px col;

	col.r = 255;
	t_pxtopx px;

	px.x1 = e->radar.len_tile * e->map.len_x + 100;
	px.y1 = 200;
	px.x2 = px.x1 + 100;
	px.y2 = px.y1;
	px = rotation_point(px, e->player.angle);
	mlxji_draw_line(e->img, &col, &px);
}

/*
** tan = sin(x) / cos(x);
*/

///////Glissement sur MUR ! Car deux etape, la premiere est X
/////// Besoin de voir Sin Cos omgbb

void		move_player(t_env *e, int dir)
{
	float temp;

	temp = e->player.pos_x + (e->player.move_speed * cos(e->player.angle)) * dir;
	if (e->map.map[round_to_inf(e->player.pos_y)][round_to_inf(temp)] == B_VIDE)
		e->player.pos_x = temp;
	temp = e->player.pos_y + (e->player.move_speed * sin(e->player.angle)) * dir;
	if (e->map.map[round_to_inf(temp)][round_to_inf(e->player.pos_x)] == B_VIDE)
		e->player.pos_y = temp;
}

void		update(t_env *e)
{
	//changer ? Car chaque fram
	if (e->key[123])
		e->player.angle -= e->player.rotate_speed;
	if (e->key[124])
		e->player.angle += e->player.rotate_speed;
	if (e->key[126])
		move_player(e, 1);
	if (e->key[125])
		move_player(e, -1);
}

int			loop(t_env *e)
{
	update(e);
	ft_bzero(e->img->data, e->height * e->width * 4);
	draw_radar(e);
	//radar(e);
	radar_full_screen(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
