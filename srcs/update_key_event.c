/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:10:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 18:48:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		update_key_event(t_env *e)
{
	t_player *player;
	player = &e->player;

	/*changer ? Car chaque fram*/
	if (e->key[123])
	{
		e->player.angle -= e->player.rotate_speed;
		vector_rotation(&player->dir.x, &player->dir.y, -player->rotate_speed);
		vector_rotation(&player->plan.x, &player->plan.y, -player->rotate_speed);
	}
	if (e->key[124])
	{
		e->player.angle += e->player.rotate_speed;
		vector_rotation(&player->dir.x, &player->dir.y, player->rotate_speed);
		vector_rotation(&player->plan.x, &player->plan.y, player->rotate_speed);
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
