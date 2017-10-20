/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:53:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/20 17:54:19 by ntoniolo         ###   ########.fr       */
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
	t_btree		*ret;

	sprite->col = x_screen;
	if (ray->side == 'x')
	{
		sprite->dist = sprite->rela.x / ray->dir.x;
		//printf("\033[31m%f / %f = %f\n\033[0m", sprite->rela.x, ray->dir.x, sprite->dist);
	}
	else
	{
		sprite->dist = sprite->rela.y / ray->dir.y;
		//printf("\033[32m%f / %f = %f\n\033[0m", sprite->rela.x, ray->dir.x, sprite->dist);
	}
	sprite->hit = 1;
	if (!(ret = btree_create_leaf(sprite)))
		exit(end_of_program(e, "Leaf doesnt create\n"));
	btree_finsert_infix_data(&e->sprite_aff, ret->content, &cmp_dist);
}

void			sprite_hit(t_ptr_env*p, t_env *e, t_ray *ray, int x_screen)
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
