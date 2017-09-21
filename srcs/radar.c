/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:03:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 19:39:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_map(t_env *e, int len_tile)
{
	int 		x;
	int			y;
	t_pxtopx	to;
	t_px		col;

	col.r = 155;
	col.g = 20;
	col.b = 10;
	y = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] == '1')
			{
				to.x1 = x * len_tile;
				to.x2 = (x + 1) * len_tile;
				to.y1 = y * len_tile;
				to.y2 = (y + 1) * len_tile;
				if (to.x1 < e->width &&
					to.y1 < e->height)
					mlxji_draw_case(e->img, &to, &col);
			}
			x++;
		}
		y++;
	}
}

static void		draw_fov(t_env *e, t_player *player, int len_tile)
{
	t_pxtopx to;

	to.x1 = (player->pos.x) * len_tile;
	to.y1 = (player->pos.y) * len_tile;
	to.x2 = (player->pos.x + player->dir.x + player->plan.x) * len_tile;
	to.y2 = (player->pos.y + player->dir.y + player->plan.y) * len_tile;
	mlxji_draw_line(e->img, &to, COL_GREEN_CLEAR);
	to.x1 = (player->pos.x) * len_tile;
	to.y1 = (player->pos.y) * len_tile;
	to.x2 = (player->pos.x + player->dir.x - player->plan.x) * len_tile;
	to.y2 = (player->pos.y + player->dir.y - player->plan.y) * len_tile;
	mlxji_draw_line(e->img, &to, COL_GREEN_CLEAR);
}

static void		draw_vector_dir(t_env *e, t_player *player, int len_tile)
{
	t_pxtopx to;


	to.x1 = player->pos.x * len_tile;
	to.y1 = player->pos.y * len_tile;
	to.x2 = (player->pos.x + player->dir.x) * len_tile;
	to.y2 = (player->pos.y + player->dir.y) * len_tile;
	mlxji_draw_line(e->img, &to, COL_ORANGE_CLEAR);
}

static void		draw_pos_player(t_env *e, t_player *player, int len_tile)
{
	int coef;
	t_px col;
	t_pxtopx to;

	col.r = 20;
	col.g = 155;
	col.b = 255;
	coef = (int)(player->pos.x * 100) % 100;
	to.x1 = (int)player->pos.x * len_tile + (len_tile * coef / 100) - len_tile / 5;
	to.x2 = (int)player->pos.x * len_tile + (len_tile * coef / 100) + len_tile / 5;
	coef = (int)(player->pos.y * 100) % 100;
	to.y1 = (int)player->pos.y * len_tile + (len_tile * coef / 100) - len_tile / 5;
	to.y2 = (int)player->pos.y * len_tile + (len_tile * coef / 100) + len_tile / 5;
	mlxji_draw_case(e->img, &to, &col);
}

void	radar(t_env *e)
{
	t_radar *radar;

	radar = &e->radar;
	draw_map(e, radar->lt);
	draw_pos_player(e, &e->player, radar->lt);
	draw_fov(e, &e->player, radar->lt);
	draw_vector_dir(e, &e->player, radar->lt);
}
