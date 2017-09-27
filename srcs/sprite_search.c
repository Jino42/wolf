/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:37:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/27 18:52:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		sprite_search(t_env *e, t_player *player)
{
	t_fvector2d	rela;
	t_fvector2d ray_dir;

	e->sprite[0].hit = 0;
	rela.x = e->sprite[0].pos.x - e->player.pos.x;
	rela.y = e->sprite[0].pos.y - e->player.pos.y;

	float my;
	float sp;
	my = (atan2f(player->dir.y, player->dir.x) * 180 / 3.1514);
	sp = (atan2f(rela.y, rela.x) * 180 / 3.1514);
	printf("My [%.2f] Sp [%.2f]\n", my, sp);
	float dif;
	dif = sp - my;
	printf("Dif %.2f\n", dif);
	float perc;

	dif += 33;
	dif /= 100;
	perc = player->len_screen / 0.66;
	perc = perc * dif;
	if (perc > 0 && perc < e->width)
	{
		e->sprite[0].hit = 1;
		e->sprite[0].col = (int)perc;
		float dist = (float)1 / ((float)33);
		dist = dist * (float)(dif * 100) - 1;
		ray_dir.x = player->dir.x + player->plan.x * dist;
		ray_dir.y = player->dir.y + player->plan.y * dist;
		int lt = e->radar.lt;
		e->to.x1 = player->pos.x * lt;
		e->to.y1 = player->pos.y * lt;
		e->to.x2 = (player->pos.x + ray_dir.x) * lt;
		e->to.y2 = (player->pos.y + ray_dir.y) * lt;
		mlxji_draw_line(e->img, &e->to, 0x0FFFF0);
	}
}
