/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/16 23:10:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
void	raycast(float angle)
{
}

void	loop_raycast_wolf(t_env *e, t_player *player)
{
	float	cam;
	int		x_screen;

	s_screen = 0;
	while (s_screen < player->len_screen)
	{
		// Need to set gen ray
		cam = (2 * x) / len_screen - 1; //inter [-1 1]
		raycast(cam);
		s_screen++;
	}
}

void	raycast_wolf(t_env *e)
{
	loop_raycast_wolf(e, &e->player)
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
		if (ray_dir_x < 0)
		{
			step_x = -1;
			f_len_x = (e->player.pos_x - (int)e->player.pos_x) * len_x;
		}
		else
		{
			step_x = 1;
			f_len_x = ((int)e->player.pos_x + 1 - e->player.pos_x) * len_x;
		}
		if (ray_dir_y < 0)
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
	//			ft_printf("%2.f Okkk !! [%i][%i]\n", x, map_y, map_x);
				hit = 1;
			}
		}
	
		float dist_w;	
		if (!last_y)
			dist_w = (map_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			dist_w = (map_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;//cos(cam);

		float wall;
		if (!last_y)
			wall = player->pos_y + dist_w * ray_dir_y;
		else
			wall = player->pos_x + dist_w * ray_dir_x;
		wall -= floor(wall);
		if (x==200)
		{
			if (!last_y)
				printf("last : x %.2f\n", fabs((map_x - player->pos_x + (1 - step_x) / 2)));
			else
				printf("last : y %.2f\n", fabs((map_y - player->pos_y + (1 - step_y) / 2)));
			printf("Dist : %.2f\n", dist_w);
			printf("Cam : %.2f\n", cam);
		}
	
		t_px col;
		t_pxtopx to;
	
		col.r = 10;
		col.b = 225;
		col.g = 50;
		int lt = e->radar.len_tile_fs;
		to.x1 = player->pos_x * lt;
		to.y1 = player->pos_y * lt;
		if (last_y)
			to.x2 = (map_x + wall) * lt;
		else
			to.x2 = (map_x + (1 - step_x) / 2) * lt;
		if (last_y)
			to.y2 = (map_y + (1 - step_y) / 2) * lt;
		else
			to.y2 = (map_y + wall) * lt;
//		printf("X1 [%i] Y1[%i] || X2 [%i] Y2[%i]\n", to.x1, to.y1, to.x2, to.y2);
		mlxji_draw_line(e->img, &col, &to);
		x++;
	}
}
