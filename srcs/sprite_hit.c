/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:53:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 18:34:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float			cmp_dist(void *item, void *insert)
{
	return (((t_sprite *)insert)->dist - ((t_sprite *)item)->dist);
}

void			sprite_hit(t_env *e, t_ray *ray, int s_screen)
{
	t_sprite	*sprite;
	int			spe_angle_ray;
	t_btree		*ret;
	t_list		*lst;

	spe_angle_ray = (int)(atan2f(ray->dir.y, ray->dir.x) * 300);
	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		if (!sprite->hit && spe_angle_ray == sprite->spe_angle)
		{
			sprite->col = s_screen;
			if (ray->side == 'x')
				sprite->dist = sprite->rela.x / ray->dir.x;
			else
				sprite->dist = sprite->rela.y / ray->dir.y;
			sprite->hit = 1;
			if (!(ret = btree_create_leaf(sprite)))
				exit(end_of_program(e, "Leaf doesnt create\n"));
			btree_finsert_infix_data(&e->sprite_aff, ret->content, &cmp_dist);
			sprite->ray_dir = ray->dir;
		}
		lst = lst->next;
	}
}
