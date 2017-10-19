/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:20:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 18:21:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		set_sprite_relative_angle(t_player *player, t_sprite *sprite)
{
	sprite->rela.x = sprite->pos.x - player->pos.x;
	sprite->rela.y = sprite->pos.y - player->pos.y;
	sprite->spe_angle = (int)(atan2f(sprite->rela.y, sprite->rela.x) * 300);
	sprite->hit = 0;
}

static void		update_sprite_acceleration(t_env *e, t_sprite *sprite)
{
	t_fvector2d dist;

	dist.x = e->player.pos.x - sprite->pos.x;
	dist.y = e->player.pos.y - sprite->pos.y;
	if (dist.x && dist.y)
	{
		sprite->acceleration.x = fvector2d_normalized(dist).x * 0.2;
		sprite->acceleration.y = fvector2d_normalized(dist).y * 0.2;
		sprite->velocity.x += sprite->acceleration.x;
		sprite->velocity.y += sprite->acceleration.y;
	}
	else
	{
		sprite->velocity.x = 0.01;
		sprite->velocity.y = 0.01;
	}
}

static void		update_sprite_new_position(t_env *e, t_sprite *sprite)
{
	t_fvector2d temp;

	temp.x = sprite->pos.x + sprite->velocity.x * e->time_frame;
	temp.y = sprite->pos.y + sprite->velocity.y * e->time_frame;
	if ((int)sprite->pos.x < e->map.len_x &&
		(int)sprite->pos.y < e->map.len_y)
	{
		if (e->map.map[(int)sprite->pos.y][(int)temp.x] == B_VOID)
			sprite->pos.x = temp.x;
		else
			sprite->velocity.x = -sprite->velocity.x;
		if (e->map.map[(int)temp.y][(int)sprite->pos.x] == B_VOID)
			sprite->pos.y = temp.y;
		else
			sprite->velocity.y = -sprite->velocity.y;
	}
}

void			update_sprite_position(t_env *e)
{
	t_list			*lst;
	t_sprite		*sprite;

	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		if (e->flag & SP_GRAVITY)
			update_sprite_acceleration(e, sprite);
		fvector2d_limit(&sprite->velocity, 3);
		update_sprite_new_position(e, sprite);
		set_sprite_relative_angle(&e->player, sprite);
		lst = lst->next;
	}
}
