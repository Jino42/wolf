/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/16 19:55:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
/*
void	raycast(t_env *e)
{
}
*/
void	test(t_env *e)
{
	float x;
	float cam;
	float ray_dir_x;
	float ray_dir_y;
	float len_x;
	float len_y;
	float f_len_x;
	float f_len_y;
	float step_x;
	float step_y;
	int len_screen;
	int hit;
	t_player *player;

	(void)f_len_y;
	(void)step_y;
	player = &e->player;
	len_screen = 400;
	x = 0;
	while (x < len_screen)
	{
		cam = (2 * x) / len_screen - 1; //inter [-1 1]
		ray_dir_x = player->dir_x + player->plan_x * cam;
		ray_dir_y = player->dir_y + player->plan_y * cam;

		if (x == len_screen / 2)
		{
			printf("\033[31m");
			printf("%.2f : %.2f %.2f\n", x, ray_dir_x, ray_dir_y);
			printf("\033[0m");
		}
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
	hit = 0; 
	int last_y; //last = 'x' 'y'
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
	//		ft_printf("%i Okkk !! [%i][%i]\n", x, map_y, map_x);
			hit = 1;
		}
	}

	float dist_w;
	if (!last_y)
		dist_w = (map_x - player->pos_x + (1 - step_x) / 2) *1 / ray_dir_x; //pour X distance, la longueur de la droite fait tant
	else
		dist_w = (map_y - player->pos_y + (1 - step_y) / 2) * 1 / ray_dir_y;
	float w_x;
	if (!last_y)
		w_x = player->pos_y + dist_w * ray_dir_y; //rescale lenght de x en Y 
	else
		w_x = player->pos_x + dist_w * ray_dir_x; 
	if(x==200)
	{
		if (last_y)
			printf("last = y : pos_x = %.2f\n", player->pos_x);
		else
			printf("last = x : pos_y = %.2f\n", player->pos_y);
		printf("Dist %.2f\n", dist_w);
		printf("w_x %.2f\n", w_x);
	}
	w_x -= floor((w_x));
	if(x==200)
		printf("w_x %.2f\n", w_x);
	t_px col;
	t_pxtopx to;

	col.r = 10;
	col.b = 225;
	col.g = 50;
	int lt = e->radar.len_tile_fs;
	to.x1 = player->pos_x * lt;
	to.y1 = player->pos_y * lt;
	if (last_y)
		to.x2 = (map_x + w_x) * lt;
	else
		to.x2 = (map_x + (1 - step_x) / 2) * lt;
	if (last_y)
		to.y2 = (map_y + (1 - step_y) / 2) * lt;
	else
		to.y2 = (map_y + w_x) * lt;
//	printf("X1 [%i] Y1[%i] || X2 [%i] Y2[%i]\n", to.x1, to.y1, to.x2, to.y2);
	mlxji_draw_line(e->img, &col, &to);
	x++;
	}
}
