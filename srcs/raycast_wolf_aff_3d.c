/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf_aff_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 23:17:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	aff_3d_basic(t_env *e, int nb_cast, int start_y, int end_y)
{
	t_pxtopx to;

	ft_bzero(&to, sizeof(t_pxtopx));
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	to.x1 = (nb_cast + 1);
	to.y1 = start_y;
	to.x2 = (nb_cast + 1);
	to.y2 = end_y;
	mlxji_draw_y_line(e->img, &to, COL_GREEN_SMOOTH);
}

static void	aff_3d_text(t_env *e, int nb_cast,
		int start_y, float len_pp, t_ray *ray)
{
	float		len;
	int			i;
	int			place_x;
	int			icol;
	t_pxtopx to;
	int			tex;

	tex = ray->get - '0';
	ft_bzero(&to, sizeof(t_pxtopx));
	to.x1 = nb_cast + 1;
	to.y2 = start_y;
	place_x = (ray->percent_wall * e->tex[tex].width);
	i = -1;
	len = 0;
	while (++i < ft_min(e->tex[tex].height, e->tex[tex].width))
	{
		to.y1 = to.y2;
		to.y2 = start_y + len;
		if (to.y2 > 0)
		{
			if (to.y1 < 0)
				to.y1 = 0;
			icol = *((int *)&e->tex[tex].tex[(place_x << 2) + i *
					(e->tex[tex].width << 2)]);
			if (to.y2 >= e->size_side)
				to.y2 = e->size_side - 1;
			mlxji_draw_y_line(e->img, &to, icol);
		}
		len += len_pp;
	}
}

static void	aff_3d_sky(t_env *e, t_ray *ray, int nb_cast, int end)
{
	int			i;
	int			text_x;
	t_pxtopx	to;
	int			icol;

	ft_bzero(&to, sizeof(t_pxtopx));
	(void)ray;
	to.x1 = nb_cast + 1;
	to.y2 = 0;
	i = 0;
	text_x = to.x1 + e->player.angle * 300;
	if (text_x < 0)
		text_x = e->tex[TEX_SKY].width - text_x;
	while (i < end)
	{
		to.y1 = to.y2;
		to.y2 = to.y1 + 1;
		icol = *((int *)&e->tex[TEX_SKY].tex[(text_x << 2) + i *
				(e->tex[TEX_SKY].width << 2)]);
		if (to.y2 >= e->size_side)
			to.y2 = e->size_side - 1;
		mlxji_draw_y_line(e->img, &to, icol);
		i++;
	}
}

static void	aff_3d_sol(t_env *e, t_ray *ray, int nb_cast, int start)
{
	t_pxtopx	to;

	(void)ray;
	to.x1 = nb_cast + 1;
	to.y1 = start - 1;
	to.y2 = e->height - 1;
	mlxji_draw_y_line(e->img, &to, 0);
}

void		raycast_wolf_aff_3d(t_env *e, t_ray *ray, int nb_cast)
{
	int		height_half_wall;
	int		start_y;
	int		end_y;
	float	len_pp;

	height_half_wall = e->size_side / ray->dist_wall / 2;
	start_y = e->size_half_side - height_half_wall;
	end_y = height_half_wall + e->size_half_side;
	len_pp = (float)(end_y - start_y) /
			ft_min(e->tex[1].height, e->tex[1].width);
	if (e->flag & F_AFF_BASIC)
		aff_3d_basic(e, nb_cast, start_y, end_y);
	else
		aff_3d_text(e, nb_cast, start_y, len_pp, ray);
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	aff_3d_sky(e, ray, nb_cast, start_y);
	aff_3d_sol(e, ray, nb_cast, end_y);
}
