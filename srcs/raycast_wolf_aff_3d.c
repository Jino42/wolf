/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf_aff_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:16:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	aff_3d_basic(t_env *e, int nb_cast, int start_y, int end_y)
{
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	e->to.x1 = (nb_cast + 1);
	e->to.y1 = start_y;
	e->to.x2 = (nb_cast + 1);
	e->to.y2 = end_y;
	mlxji_draw_y_line(e->img, &e->to, COL_GREEN_SMOOTH);
}

static void	aff_3d_text(t_env *e, int nb_cast,
		int start_y, float len_pp)
{
	float		len;
	int			i;
	int			place_x;

	e->to.x1 = nb_cast + 1;
	e->to.y2 = start_y;
	place_x = (e->ray.percent_wall * e->tex[1].width);
	i = -1;
	len = 0;
	while (++i < ft_min(e->tex[1].height, e->tex[1].width))
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

void		raycast_wolf_aff_3d(t_env *e, t_ray *ray, int nb_cast)
{
	int		height_half_wall;
	int		start_y;
	int		end_y;
	float	len_pp;

	height_half_wall = e->size_side / ray->dist_wall / 2;
	start_y = e->size_half_side - height_half_wall + e->player.jump;
	end_y = height_half_wall + e->size_half_side + e->player.jump;
	len_pp = (float)(end_y - start_y) /
		ft_min(e->tex[1].height, e->tex[1].width);
	if (e->flag & F_AFF_BASIC)
		aff_3d_basic(e, nb_cast, start_y, end_y);
	else
		aff_3d_text(e, nb_cast, start_y, len_pp);
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	aff_3d_sky(e, ray, nb_cast, start_y);
}
