/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 22:36:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		direction_raycast(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->len.x = (ray->start.x - ray->pos_map.x) * ray->delta_len.x;
	}
	else
	{
		ray->step_x = 1;
		ray->len.x = (ray->pos_map.x + 1 - ray->start.x) * ray->delta_len.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->len.y = (ray->start.y - ray->pos_map.y) * ray->delta_len.y;
	}
	else
	{
		ray->step_y = 1;
		ray->len.y = (ray->pos_map.y + 1 - ray->start.y) * ray->delta_len.y;
	}
}

void			init_raycast(t_ray *ray, t_map *map,
							t_fvector2d start, t_fvector2d dir)
{
	ray->map = map;
	ray->pos_map.x = (int)start.x;
	ray->pos_map.y = (int)start.y;
	ray->start.x = start.x;
	ray->start.y = start.y;
	ray->dir.y = dir.y;
	ray->dir.x = dir.x;
	ray->delta_len.x = sqrt(1 + (pow(ray->dir.y, 2) /
								pow(ray->dir.x, 2)));
	ray->delta_len.y = sqrt(1 + (pow(ray->dir.x, 2) /
								pow(ray->dir.y, 2)));
	direction_raycast(ray);
}

static int		raycast_hit(t_ray *ray)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->pos_map.x += ray->step_x;
			ray->len.x += ray->delta_len.x;
			ray->side = 'x';
		}
		else
		{
			ray->pos_map.y += ray->step_y;
			ray->len.y += ray->delta_len.y;
			ray->side = 'y';
		}
		if (ray->map->map[ray->pos_map.y][ray->pos_map.x] != B_VOID)
			ray->hit = 1;
	}
	return (ray->hit);
}

static void		raycast_dist_wall(t_ray *ray)
{
	if (ray->side == 'x')
		ray->dist_wall = (ray->pos_map.x - ray->start.x +
							(1 - ray->step_x) / 2) / ray->dir.x;
	else
		ray->dist_wall = (ray->pos_map.y - ray->start.y +
							(1 - ray->step_y) / 2) / ray->dir.y;
	if (ray->side == 'x')
		ray->percent_wall = ray->start.y + ray->dist_wall * ray->dir.y;
	else
		ray->percent_wall = ray->start.x + ray->dist_wall * ray->dir.x;
	ray->percent_wall -= (int)ray->percent_wall;
	if (ray->side == 'x')
		ray->end.x = (ray->pos_map.x + (1 - ray->step_x) / 2);
	else
		ray->end.x = (ray->pos_map.x + ray->percent_wall);
	if (ray->side == 'y')
		ray->end.y = (ray->pos_map.y + (1 - ray->step_y) / 2);
	else
		ray->end.y = (ray->pos_map.y + ray->percent_wall);
}

int				raycast(t_ray *ray, t_map *map,
						t_fvector2d start, t_fvector2d dir)
{
	init_raycast(ray, map, start, dir);
	if (!raycast_hit(ray))
		return (0);
	raycast_dist_wall(ray);
	return (1);
}
