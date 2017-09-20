/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/20 20:35:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	raycast_wolf_aff_2d(t_env *e, t_player *player,
		t_ray *ray, int lt)
{
	e->col.r = 100;
	e->col.g = 0;
	e->col.b = 0;
	e->to.x1 = player->pos_x * lt;
	e->to.y1 = player->pos_y * lt;
	e->to.x2 = ray->end.x * lt;
	e->to.y2 = ray->end.y * lt;
	mlxji_draw_line(e->img, &e->col, &e->to);
}

void		draw_y_line(t_img *img, t_px *px, t_pxtopx *to)
{
	while (to->y1 < to->y2)
	{
		img->data[to->x1 * 4 + to->y1 * img->size_line] = px->b;
		img->data[to->x1 * 4 + to->y1 * img->size_line + 1] = px->g;
		img->data[to->x1 * 4 + to->y1 * img->size_line + 2] = px->r;
		to->y1++;
	}
}

static void	aff_3d_basic(t_env *e, int nb_cast, int start_y, int end_y)
{
	e->col.r = 10;
	e->col.b = 50;
	e->col.g = 100;
	e->to.x1 = (nb_cast+1);
//	to.x1 = ((nb_cast+1)) * e->width / player->len_screen;
	e->to.y1 = start_y;
	e->to.x2 = (nb_cast+1);
//	to.x2 = ((nb_cast+2)) * e->width / player->len_screen;
	e->to.y2 = end_y;
//	mlxji_draw_case(e->img, &to, &col); LEEN
	draw_y_line(e->img, &e->col, &e->to);
}

static void	aff_3d_text(t_env *e, t_ray *ray, int nb_cast, int start_y, float len_pp)
{
	float		len;
	int			i;
	int			place_x;

	e->to.x1 = nb_cast + 1;
	e->to.y2 = start_y;
	place_x = ray->percent_wall * 64;
	i = 0;
	len = 0;
	while (i < 64)
	{
		e->to.y1 = e->to.y2;
		e->to.y2 = start_y + len;
		if (e->to.y2 > 0)
		{
			if (e->to.y1 < 0)
				e->to.y1 = 0;
			e->col.b = e->text[place_x * 4 + i * TEXT_Y * 4 + 0];
			e->col.g = e->text[place_x * 4 + i * TEXT_Y * 4 + 1];
			e->col.r = e->text[place_x * 4 + i * TEXT_Y * 4 + 2];
			if (e->to.y2 >= e->size_side)
				e->to.y2 = e->size_side - 1;
			draw_y_line(e->img, &e->col, &e->to);
		}
		len += len_pp;
		i++;
	}
}

static void	raycast_wolf_aff_3d(t_env *e, t_player *player, t_ray *ray, int nb_cast)
{
	int	height_half_wall;
	int start_y;
	int end_y;
	float	len_pp;

	(void)player;
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
		len_pp = (float)(end_y - start_y) / TEXT_Y;
		aff_3d_text(e, ray, nb_cast, start_y, len_pp);
	}/*
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	len_pp = (float)(start_y) / TEXT_Y;
	aff_3d_text(e, ray, nb_cast, 0, len_pp);*/
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
		raycast_wolf_aff_2d(e, player, &ray, e->radar.lt);
		if (e->flag & F_3D)
			raycast_wolf_aff_3d(e, player, &ray, s_screen);
		s_screen++;
	}
}
