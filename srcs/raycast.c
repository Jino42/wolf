/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/16 15:28:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	test(t_env *e)
{
	int x;
	double cam;
	double ray_dir_x;
	double ray_dir_y;
	double len_x;
	double len_y;
	double f_len_x;
	double f_len_y;
	double step_x;
	double step_y;
	int len_screen;
	int hit;
	t_player *player;

	(void)f_len_y;
	(void)step_y;
	player = &e->player;
	len_screen = 320;
	x = 0;
	while (x < len_screen)
	{
		cam = 2 * x / len_screen - 1; //inter [-1 1]
		ray_dir_x = player->dir_x + player->plan_x * cam;
		ray_dir_y = player->dir_y + player->plan_y * cam;

		//need len per [x] and [y]
		len_x = sqrt(1+(pow(ray_dir_y, 2) / pow(ray_dir_x, 2)));
		len_y = sqrt(1+(pow(ray_dir_x, 2) / pow(ray_dir_y, 2)));
		if (player->dir_x < 0)
		{
			step_x = -1;
			f_len_x = (e->player.pos_x - (int)e->player.pos_x) * len_x;
		}
		else
		{
			step_x = 1;
			f_len_x = ((int)e->player.pos_x + 1 - e->player.pos_x) * len_x;
		}
		if (player->dir_y < 0)
		{
			step_y = -1;
			f_len_y = (e->player.pos_y - (int)e->player.pos_y) * len_y;
		}
		else
		{
			step_y = 1;
			f_len_y = ((int)e->player.pos_y + 1 - e->player.pos_y) * len_y;
		}
		x++;
	}
	hit = 0; 
	int last_y;
	int map_x = (int)player->pos_x;
	int map_y = (int)player->pos_y;
	while (!hit)
	{
		if (f_len_x < f_len_y)
		{
			map_x += step_x;
			f_len_x += len_x; 
			last_y = 0;
		}
		else
		{
			map_y += step_y;
			f_len_y += len_y;
			last_y = 1;
		}
		if (e->map.map[map_y][map_x] != B_VOID)
		{
			ft_printf("Okkk !! [%i][%i]\n", map_y, map_x);
			hit = 1;
		}
	}
	t_px col;
	t_pxtopx to;

	col.r = 10;
	col.b = 225;
	col.g = 50;
	int lt = e->radar.len_tile_fs;
	to.x1 = player->pos_x * lt;
	to.y1 = player->pos_y * lt;
	to.x2 = map_x * lt;
	to.y2 = (map_y) * lt;
	printf("X1 [%i] Y1[%i] || X2 [%i] Y2[%i]\n", to.x1, to.y1, to.x2, to.y2);
	mlxji_draw_line(e->img, &col, &to);
}
