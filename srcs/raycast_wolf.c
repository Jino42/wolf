/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:09:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycast_wolf_aff_2d(t_env *e, t_player *player,
		t_ray *ray, int lt)
{
	e->to.x1 = player->pos.x * lt;
	e->to.y1 = player->pos.y * lt;
	e->to.x2 = ray->end.x * lt;
	e->to.y2 = ray->end.y * lt;
	mlxji_draw_line(e->img, &e->to, COL_RED_SMOOTH);
}

void		raycast_wolf(t_env *e, t_player *player)
{
	t_fvector2d	ray_dir;
	t_fvector2d	ray_start;
	float		cam;
	float		s_screen;

	int loc;

	loc = 0;
	ft_bzero(&e->ray, sizeof(t_ray));
	s_screen = 0;
	while (s_screen < e->player.len_screen + 2)
	{
		cam = (s_screen * 2) / player->len_screen - 1; //inter [-1 1]
		ray_dir.x = player->dir.x + player->plan.x * cam;
		ray_dir.y = player->dir.y + player->plan.y * cam;
		ray_start.x = player->pos.x;
		ray_start.y = player->pos.y;
		raycast(&e->ray, &e->map, ray_start, ray_dir);
		raycast_wolf_aff_2d(e, player, &e->ray, e->radar.lt);
		e->dist[(int)s_screen] = e->ray.dist_wall;
		if (e->flag & F_3D)
			raycast_wolf_aff_3d(e, &e->ray, s_screen);
		sprite_hit(e, &e->ray, s_screen);
		s_screen++;
	}
}
