/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 23:12:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Glissement sur MUR ! Car deux etape
**Besoin de voir Sin Cos omgbb
*/

static void	update_fps(t_env *e, t_fps *fps)
{
	gettimeofday(&fps->step2, NULL);
	//dif seconde too 
	e->time_frame = (float)(fps->step2.tv_usec - fps->cur.tv_usec) / 1000000;
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

void		vec_test(t_env *e)
{
	t_player *player;
	player = &e->player;
	int i;
	t_sprite *sprite;
	float	speed;
	float delta_frame;

	delta_frame = 0.017;
	t_fvector2d temp;
	speed = 2;
//	if (e->fps.ret_fps)
//		delta_frame = 1 / (float)e->fps.ret_fps;
	t_fvector2d vel;
	t_fvector2d nor;
	t_fvector2d dist;
	i = 0;
	while (i < NB_SPRITE)
	{
		sprite = &e->sprite[i];
		dist.x = e->player.pos.x - sprite->pos.x;
		dist.y = e->player.pos.y - sprite->pos.y;
		float len = sqrt(fabs(dist.x)*2 + fabs(dist.y)*2);
		nor.x = dist.x / len;
		nor.y = dist.y / len;
		vel.x = nor.x * speed;
		vel.y = nor.y * speed;
		temp.x = sprite->pos.x + vel.x * delta_frame;
		temp.y = sprite->pos.y + vel.y * delta_frame;
		if (e->map.map[(int)sprite->pos.y][(int)temp.x] == B_VOID)
			sprite->pos.x = temp.x;
		if (e->map.map[(int)temp.y][(int)sprite->pos.x] == B_VOID)
			sprite->pos.y = temp.y;
		i++;
	}
}

int			loop(t_env *e)
{
	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e, &e->player);
	ft_bzero(e->img->data, e->height * e->width * 4);
	raycast_wolf(e, &e->player);
	sprite_wolf(e, &e->sprite[0]);
	sprite_wolf(e, &e->sprite[1]);
	radar(e);
	vec_test(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
