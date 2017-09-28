/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 15:54:46 by ntoniolo         ###   ########.fr       */
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

void		update_sprite_position(t_env *e, t_player *player)
{
	//ia move ?
	t_sprite	*sprite;
	int			i;

	i = 0;
	while (i < NB_SPRITE)
	{
		sprite = &e->sprite[i];
		sprite->rela.x = sprite->pos.x - player->pos.x;
		sprite->rela.y = sprite->pos.y - player->pos.y;
		sprite->spe_angle = (int)(atan2f(sprite->rela.y, sprite->rela.x) * 300);
		sprite->hit = 0;
		i++;
	}
}

int			loop(t_env *e)
{
	update_fps(&e->fps);
	update_key_event(e);
	update_sprite_position(e, &e->player);
	ft_bzero(e->img->data, e->height * e->width * 4);
	raycast_wolf(e, &e->player);
	sprite_search(e, &e->player);
	sprite_wolf(e, &e->sprite[0]);
	sprite_wolf(e, &e->sprite[1]);
	radar(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
