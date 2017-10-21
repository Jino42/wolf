/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 20:44:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		raycast_aff(t_env *e, t_ray *ray, int nb_cast)
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
		raycast_aff_basic(e, nb_cast, start_y, end_y, ray);
	else
		raycast_aff_tex(e, nb_cast, start_y, len_pp, ray);
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	raycast_aff_sky(e, nb_cast, start_y);
	raycast_aff_floor(e, nb_cast, end_y);
}
