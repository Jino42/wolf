/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/27 19:11:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Glissement sur MUR ! Car deux etape
**Besoin de voir Sin Cos omgbb
*/

void		update_fps(t_fps *fps)
{
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
		ft_printf("FPS [%i]\n", fps->ret_fps);
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
	}
	fps->fps++;
}

int			loop(t_env *e)
{
	update_fps(&e->fps);
	update_key_event(e);
	ft_bzero(e->img->data, e->height * e->width * 4);
	raycast_wolf(e, &e->player);
	radar(e);
	//sprite_search(e, &e->player);
	//sprite_wolf(e, &e->sprite[0], &e->player);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
