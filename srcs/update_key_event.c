/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:10:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/20 19:30:19 by ntoniolo         ###   ########.fr       */
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
		vector_rotation(&player->dir_x, &player->dir_y, -player->rotate_speed);
		vector_rotation(&player->plan_x, &player->plan_y, -player->rotate_speed);
	}
	if (e->key[124])
	{
		e->player.angle += e->player.rotate_speed;
		vector_rotation(&player->dir_x, &player->dir_y, player->rotate_speed);
		vector_rotation(&player->plan_x, &player->plan_y, player->rotate_speed);
	}
	if (e->key[126])
		move_player(e, 1);
	if (e->key[125])
		move_player(e, -1);
	if (e->key[31])
	{
		e->player.dir_x *= 1.1;
		e->player.dir_y *= 1.1;
	}
	if (e->key[37])
	{
		e->player.dir_x *= 0.9;
		e->player.dir_y *= 0.9;
	}
	if (e->key[91])
		player->jump += 1;
	if (e->key[84])
		player->jump -= 1;
	if (e->key[78])
	{
		player->dir_x *= 0.9;
		player->dir_y *= 0.9;
	}
	if (e->key[69])
	{
		player->dir_x *= 1.1;
		player->dir_y *= 1.1;
	}
}
