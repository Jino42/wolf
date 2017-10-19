/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 17:34:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Glissement sur MUR ! Car deux etape
*/

static void	update_fps(t_env *e, t_fps *fps)
{
	gettimeofday(&fps->step2, NULL);
	if (e->s)
	{
		e->time_frame = (float)(fps->step2.tv_usec - fps->cur.tv_usec) / 1000000;
		if (e->time_frame < 0.005)
			e->time_frame = 0.005;
		if (fps->cur.tv_sec != fps->step2.tv_sec)
			e->time_frame = (float)(fps->step2.tv_usec + (1000000 - fps->cur.tv_usec)) / 1000000;
	}
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
		ft_printf("FPS [%i]\n", fps->ret_fps);
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
		e->s++;
	}
	fps->fps++;
}

void 		wolf_free_btree(void *item)
{
	(void)item;
	return ;
}

int			loop(t_env *e)
{
	if (!(e->flag & F_3D))
		ft_bzero(e->img->data, e->width * e->height * 4);
	ft_bzero(e->apply, sizeof(int) * (WIN_WIDTH + 10));
	ft_bzero(e->ray_end, sizeof(t_fvector2d) * (WIN_WIDTH + 10));
	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e);
	raycast_wolf(e, &e->player);
	if (e->sprite_aff)
	{
		btree_env_apply_infix(e, e->sprite_aff, &sprite_wolf);
		btree_apply_free(e->sprite_aff, &wolf_free_btree);
		e->sprite_aff = NULL;
	}
	radar(e);
	//vec_test(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
