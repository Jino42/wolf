/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:03:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/13 23:22:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void draw_player(t_env *e, t_radar *radar)
{
	int coef;
	t_pxtopx to;
	t_px	col;

	col.r = 20;
	col.g = 155;
	col.b = 255;
	coef = (int)(e->player.pos_x * 100) % 100;
	to.x1 = (int)e->player.pos_x * radar->len_tile + (radar->len_tile * coef / 100) - 1;
	to.x2 = (int)e->player.pos_x * radar->len_tile + (radar->len_tile * coef / 100) + 1;
	coef = (int)(e->player.pos_y * 100) % 100;
	to.y1 = (int)e->player.pos_y * radar->len_tile + (radar->len_tile * coef / 100) - 1;
	to.y2 = (int)e->player.pos_y * radar->len_tile + (radar->len_tile * coef / 100) + 1;
	mlxji_draw_case(e->img, &to, &col);

}

void	draw_map(t_env *e, t_radar *radar)
{
	int 		x;
	int			y;
	t_pxtopx	to;
	t_px		col;

	col.r = 255;
	col.g = 0;
	col.b = 0;
	y = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] == '1')
			{
				to.x1 = x * radar->len_tile;
				to.x2 = (x + 1) * radar->len_tile;
				to.y1 = y * radar->len_tile;
				to.y2 = (y + 1) * radar->len_tile;
				mlxji_draw_case(e->img, &to, &col);
			}
			x++;
		}
		y++;
	}
	draw_player(e, radar);
}

void	radar(t_env *e)
{
	draw_map(e, &e->radar);
	draw_player(e, &e->radar);
}

void	draw_map_full_screen(t_env *e, t_radar *radar)
{
	int 		x;
	int			y;
	t_pxtopx	to;
	t_px		col;

	col.r = 255;
	col.g = 0;
	col.b = 0;
	y = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] == '1')
			{
				to.x1 = x * radar->len_tile_fs;
				to.x2 = (x + 1) * radar->len_tile_fs;
				to.y1 = y * radar->len_tile_fs;
				to.y2 = (y + 1) * radar->len_tile_fs;
				mlxji_draw_case(e->img, &to, &col);
			}
			x++;
		}
		y++;
	}
}

static void draw_player_full_screen(t_env *e, t_radar *radar)
{
	int coef;
	t_pxtopx to;
	t_px	col;

	col.r = 20;
	col.g = 155;
	col.b = 255;
	coef = (int)(e->player.pos_x * 100) % 100;
	to.x1 = (int)e->player.pos_x * radar->len_tile_fs + (radar->len_tile_fs * coef / 100) - 10;
	to.x2 = (int)e->player.pos_x * radar->len_tile_fs + (radar->len_tile_fs * coef / 100) + 10;
	coef = (int)(e->player.pos_y * 100) % 100;
	to.y1 = (int)e->player.pos_y * radar->len_tile_fs + (radar->len_tile_fs * coef / 100) - 10;
	to.y2 = (int)e->player.pos_y * radar->len_tile_fs + (radar->len_tile_fs * coef / 100) + 10;
	mlxji_draw_case(e->img, &to, &col);
	//Pivoter Vector sur matrice de rotation
}

void	radar_full_screen(t_env *e)
{
	draw_map_full_screen(e, &e->radar);
	draw_player_full_screen(e, &e->radar);
}
