/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:53:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/01 17:55:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		sprite_hit(t_env *e, t_ray *ray, int s_screen)
{
	t_sprite	*sprite;
	int			i;
	int			spe_angle_ray;

	spe_angle_ray = (int)(atan2f(ray->dir.y, ray->dir.x) * 300);
	i = 0;
	while (i < NB_SPRITE)
	{
		sprite = &e->sprite[i];
		if (!sprite->hit && spe_angle_ray == sprite->spe_angle)
		{
			sprite->col = s_screen;
			if (ray->side == 'x')
				sprite->dist = sprite->rela.x / ray->dir.x;
			else
				sprite->dist = sprite->rela.y / ray->dir.y;
			sprite->hit = 1;
			sprite->ray_dir = ray->dir;
		}
		i++;
	}
}
