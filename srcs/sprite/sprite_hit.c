/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:53:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 22:20:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float			cmp_dist(void *item, void *insert)
{
	return (((t_sprite *)insert)->dist - ((t_sprite *)item)->dist);
}

static void		sprite_is_hit(t_env *e, t_ray *ray,
								int x_screen, t_sprite *sprite)
{
	sprite->col = x_screen;
	if (ray->side == 'x')
		sprite->dist = sprite->rela.x / ray->dir.x;
	else
		sprite->dist = sprite->rela.y / ray->dir.y;
	sprite->hit = 1;
	btree_finsert_infix_data(&e->sprite_aff, sprite, &cmp_dist);
}

void			sprite_hit(t_ptr_env *p, t_env *e, t_ray *ray, int x_screen)
{
	t_sprite	*sprite;
	int			spe_angle_ray;
	t_list		*lst;
	t_fvector2d norm;

	spe_angle_ray = (int)(atan2f(ray->dir.y, ray->dir.x) * 300);
	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		norm = sprite->rela;
		fvector2d_normalize(&norm);
		if (!sprite->hit && spe_angle_ray == sprite->spe_angle)
		{
			pthread_mutex_lock(&p->e->mutex);
			sprite_is_hit(e, ray, x_screen, sprite);
			pthread_mutex_unlock(&p->e->mutex);
		}
		lst = lst->next;
	}
}
