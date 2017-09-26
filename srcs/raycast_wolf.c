/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/26 15:37:55 by ntoniolo         ###   ########.fr       */
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

static void	aff_3d_basic(t_env *e, int nb_cast, int start_y, int end_y)
{
	e->to.x1 = (nb_cast + 1);
	e->to.y1 = start_y;
	e->to.x2 = (nb_cast + 1);
	e->to.y2 = end_y;
	mlxji_draw_y_line(e->img, &e->to, COL_GREEN_SMOOTH);
}

static void	aff_3d_text(t_env *e, t_ray *ray, int nb_cast,
		int start_y, float len_pp)
{
	float		len;
	int			i;
	int			place_x;

	e->to.x1 = nb_cast + 1;
	e->to.y2 = start_y;
	place_x = (ray->percent_wall * e->tex[1].width);
	i = 0;
	len = 0;
	while (i < ft_min(e->tex[1].height, e->tex[1].width))
	{
		e->to.y1 = e->to.y2;
		e->to.y2 = start_y + len;
		if (e->to.y2 > 0)
		{
			if (e->to.y1 < 0)
				e->to.y1 = 0;
			e->icol = *((int *)&e->tex[1].tex[(place_x << 2) + i *
					(e->tex[1].width << 2)]);
			if (e->to.y2 >= e->size_side)
				e->to.y2 = e->size_side - 1;
			mlxji_draw_y_line(e->img, &e->to, e->icol);
		}
		len += len_pp;
		i++;
	}
}

static void	aff_3d_sky(t_env *e, t_ray *ray, int nb_cast, int end)
{
	int			i;
	int			text_x;

	(void)ray;
	e->to.x1 = nb_cast + 1;
	e->to.y2 = 0;
	i = 0;
	text_x = e->to.x1 + e->player.angle * 300;
	if (text_x < 0)
		text_x = e->tex[TEX_SKY].width - text_x;
	while (i < end)
	{
		e->to.y1 = e->to.y2;
		e->to.y2 = e->to.y1 + 1;
		e->icol = *((int *)&e->tex[TEX_SKY].tex[(text_x << 2) + i *
				(e->tex[TEX_SKY].width << 2)]);
		if (e->to.y2 >= e->size_side)
			e->to.y2 = e->size_side - 1;
		mlxji_draw_y_line(e->img, &e->to, e->icol);
		i++;
	}
}

static void	raycast_wolf_aff_3d(t_env *e, t_ray *ray, int nb_cast)
{
	int		height_half_wall;
	int		start_y;
	int		end_y;
	float	len_pp;

	height_half_wall = e->size_side / ray->dist_wall / 2;
	start_y = e->size_half_side - height_half_wall + e->player.jump;
	end_y = height_half_wall + e->size_half_side + e->player.jump;
	if (e->flag & F_AFF_BASIC)
	{
		if (end_y >= e->size_side)
			end_y = e->size_side - 1;
		if (start_y < 0)
			start_y = 0;
		aff_3d_basic(e, nb_cast, start_y, end_y);
	}
	else
	{
		len_pp = (float)(end_y - start_y) / ft_min(e->tex[1].height, e->tex[1].width);
		aff_3d_text(e, ray, nb_cast, start_y, len_pp);
	}
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	aff_3d_sky(e, ray, nb_cast, start_y);
}

void		raycast_wolf(t_env *e, t_player *player)
{
	t_fvector2d	ray_dir;
	t_fvector2d	ray_start;
	float		cam;
	float		s_screen;
	t_ray		ray;
	t_fvector2d rela;

	rela.x = e->sprite.pos.x - e->player.pos.x;
	rela.y = e->sprite.pos.y - e->player.pos.y;

	int angle;
	angle = (int)(atan2f(rela.y, rela.x) * 600);
	e->sprite.hit = 0;
	ft_bzero(&ray, sizeof(t_ray));
	s_screen = 0;
	while (s_screen < e->player.len_screen + 2)
	{
		cam = (s_screen * 2) / player->len_screen - 1; //inter [-1 1]
		ray_dir.x = player->dir.x + player->plan.x * cam;
		ray_dir.y = player->dir.y + player->plan.y * cam;
		int loc;
		if (!e->sprite.hit) //sprite besoin + :3 VERIF SI PAS OBLIGER ATAN ALL TIME
			//Une fois et si inter alors ok et find
		{
		   	loc	= (int)(atan2f(ray_dir.y, ray_dir.x) * 600);
			if (loc == angle)
			{
				e->sprite.col = s_screen;
				e->sprite.dist = sqrt(pow(rela.y, 2) + pow(rela.x, 2));
				e->sprite.hit = 1;
			}
		}
		ray_start.x = player->pos.x;
		ray_start.y = player->pos.y;
		raycast(&ray, &e->map, ray_start, ray_dir);
		raycast_wolf_aff_2d(e, player, &ray, e->radar.lt);
		if (e->flag & F_3D)
			raycast_wolf_aff_3d(e, &ray, s_screen);
		e->dist[(int)s_screen] = ray.dist_wall;
//		if (s_screen == player->len_screen / 2)
//			printf("Dist_wall : %.2f\nDist sprite %.2f\n", ray.dist_wall,
//					e->sprite.dist);
		s_screen++;
	}
}
