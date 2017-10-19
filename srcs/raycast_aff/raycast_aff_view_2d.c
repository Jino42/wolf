/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff_view_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 19:53:28 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 19:53:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		raycast_aff_view_2d(t_env *e, t_player *player)
{
	int i;
	int lt;
	int incr;

	i = 0;
	lt = e->radar.lt;
	e->to.x1 = player->pos.x * lt;
	e->to.y1 = player->pos.y * lt;
	incr = (e->flag & F_3D ? 16 : 1);
	while (i < e->width)
	{
		e->to.x2 = e->ray_end[i].x * lt;
		e->to.y2 = e->ray_end[i].y * lt;
		mlxji_draw_line(e->img, &e->to, COL_RED_SMOOTH);
		i += incr;
	}
}
