/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:20:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 22:34:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_player(t_env *e, int dir)
{
	float temp;

	temp = e->player.pos.x + (e->player.move_speed
								* cos(e->player.angle)) * dir;
	if (e->map.map[(int)e->player.pos.y][(int)temp] == B_VOID)
		e->player.pos.x = temp;
	temp = e->player.pos.y + (e->player.move_speed
								* sin(e->player.angle)) * dir;
	if (e->map.map[(int)temp][(int)e->player.pos.x] == B_VOID)
		e->player.pos.y = temp;
}
