/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:20:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/15 15:14:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_player(t_env *e, int dir)
{
	float temp;

	temp = e->player.pos_x + (e->player.move_speed * cos(e->player.angle)) * dir;
	if (e->map.map[round_to_inf(e->player.pos_y)][round_to_inf(temp)] == B_VOID)
		e->player.pos_x = temp;
	temp = e->player.pos_y + (e->player.move_speed * sin(e->player.angle)) * dir;
	if (e->map.map[round_to_inf(temp)][round_to_inf(e->player.pos_x)] == B_VOID)
		e->player.pos_y = temp;
}
