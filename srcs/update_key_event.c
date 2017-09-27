/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:10:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/27 22:46:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		update_key_event(t_env *e)
{
	t_player *player;
	player = &e->player;

	/*changer ? Car chaque fram*/
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
	if (e->key[126])
		move_player(e, 1);
	if (e->key[125])
		move_player(e, -1);
	if (e->key[31])
	{
		e->player.dir.x *= 1.1;
		e->player.dir.y *= 1.1;
	}
	if (e->key[37])
	{
		e->player.dir.x *= 0.9;
		e->player.dir.y *= 0.9;
	}
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
