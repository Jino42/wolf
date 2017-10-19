/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 19:46:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			wolf_free_btree(void *item)
{
	(void)item;
	return ;
}

static void			wolf_aff_sprite(t_env *e)
{
	if (e->sprite_aff)
	{
		btree_env_apply_infix(e, e->sprite_aff, &sprite_wolf);
		btree_apply_free(e->sprite_aff, &wolf_free_btree);
		e->sprite_aff = NULL;
	}
}

int					loop(t_env *e)
{
	//
	if (!(e->flag & F_3D))
		ft_bzero(e->img->data, e->width * e->height * 4);
	ft_bzero(e->apply, sizeof(int) * (WIN_WIDTH + 10));
	ft_bzero(e->ray_end, sizeof(t_fvector2d) * (WIN_WIDTH + 10));
	//
	//

	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e);
	//
	raycast_wolf(e, &e->player);
	wolf_aff_sprite(e);
	radar(e);
	raycast_aff_view_2d(e, &e->player);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
