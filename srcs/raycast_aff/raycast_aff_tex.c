/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 20:56:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 21:25:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			raycast_aff_tex(t_env *e, int start_y, float len_pp,
															t_ray *ray)
{
	float		len;
	int			i;
	int			place_x;
	t_pxtopx	to;
	t_tex		*tex;

	tex = &e->tex[ray->get - '0'];
	to.x1 = ray->x_screen + 1;
	to.y2 = start_y;
	place_x = (ray->percent_wall * tex->width);
	i = -1;
	len = 0;
	while (++i < ft_min(tex->height, tex->width))
	{
		to.y1 = to.y2;
		to.y2 = start_y + len;
		if (to.y2 > 0)
		{
			to.y1 < 0 ? (to.y1 = 0) : 0;
			to.y2 >= e->size_side ? (to.y2 = e->size_side - 1) : 0;
			mlxji_draw_y_line(e->img, &to,
				*((int *)&tex->tex[(place_x << 2) + i * (tex->width << 2)]));
		}
		len += len_pp;
	}
}
