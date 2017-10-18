/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:10:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/17 18:50:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	update_key_rotate(t_env *e, t_player *player)
{
	if (e->key[123] || e->key[1])
	{
		if (e->key[123])
			e->player.angle -= e->player.rotate_speed;
		else
			e->player.angle -= 0.01;
		fvector_rotation(&player->dir, -player->rotate_speed);
		fvector_rotation(&player->plan, -player->rotate_speed);
	}
	if (e->key[124] || e->key[2])
	{
		if (e->key[124])
			e->player.angle += e->player.rotate_speed;
		else
			e->player.angle += 0.01;
		fvector_rotation(&player->dir, player->rotate_speed);
		fvector_rotation(&player->plan, player->rotate_speed);
	}
}

static void	update_key_player(t_env *e, t_player *player)
{
	update_key_rotate(e, player);
	if (e->key[126])
		move_player(e, 1);
	if (e->key[125])
		move_player(e, -1);
	if (e->key[91])
		player->jump += 1;
	if (e->key[84])
		player->jump -= 1;
	if (e->key[78])
	{
		player->dir.x *= 0.9;
		player->dir.y *= 0.9;
	}
	if (e->key[69])
	{
		player->dir.x *= 1.1;
		player->dir.y *= 1.1;
	}
}

void		update_key_event(t_env *e)
{
	update_key_player(e, &e->player);
}
