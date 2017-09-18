/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/18 20:33:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	raycast_wolf_aff_2d(t_env *e, t_player *player,
		t_ray *ray, int lt)
{
	t_pxtopx to;

	e->col.r = 100;
	to.x1 = player->pos_x * lt;
	to.y1 = player->pos_y * lt;
	to.x2 = ray->end.x * lt;
	to.y2 = ray->end.y * lt;
	mlxji_draw_line(e->img, &e->col, &to);
}

static void	raycast_wolf_aff_3d(t_env *e, t_player *player, t_ray *ray, int nb_cast)
{
	int	height_half_wall;
	int start_y;
	int end_y;
	t_pxtopx to;
	t_px	col;

	(void)player;
	col.r = 10;
	col.b = 50;
	col.g = 100;
	height_half_wall = e->size_side / ray->dist_wall / 2;
	start_y = e->size_half_side - height_half_wall + e->player.jump;
	end_y = height_half_wall + e->size_half_side + e->player.jump;
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	to.x1 = (nb_cast+1);
//	to.x1 = ((nb_cast+1)) * e->width / player->len_screen;
	to.y1 = start_y;
	to.x2 = (nb_cast+1);
//	to.x2 = ((nb_cast+2)) * e->width / player->len_screen;
	to.y2 = end_y;
//	mlxji_draw_case(e->img, &to, &col); LEENN
	mlxji_draw_line(e->img, &col, &to);
}

void		raycast_wolf(t_env *e, t_player *player)
{
	t_fvector2d	ray_dir;
	t_fvector2d	ray_start;
	float	cam;
	float	s_screen;
	t_ray ray;

	ft_bzero(&ray, sizeof(t_ray));
	s_screen = 0;
	while (s_screen < e->player.len_screen)
	{
		cam = (2 * s_screen) / player->len_screen - 1; //inter [-1 1]
		ray_dir.x = player->dir_x + player->plan_x * cam;
		ray_dir.y = player->dir_y + player->plan_y * cam;
		ray_start.x = player->pos_x;
		ray_start.y = player->pos_y;	
		raycast(&ray, &e->map, ray_start, ray_dir);
		raycast_wolf_aff_2d(e, player, &ray, e->radar.len_tile);
		raycast_wolf_aff_3d(e, player, &ray, s_screen);
		s_screen++;
	}
}
