/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:37:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 00:32:54 by ntoniolo         ###   ########.fr       */
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
	my = (atan2f(player->dir.y, player->dir.x) * 180 / 3.141592653589793);
	sp = (atan2f(rela.y, rela.x) * 180 / 3.141592653589793);
	float dif;
	dif = sp - my;
	float perc;

//	my = atan2f(player->dir.y, player->dir.x);
//	sp = atan2f(rela.y, rela.x);
//	float tan_my;
//	float tan_sp;
	float jpp;
	jpp = 1 << 10;
	int a = 33;
	a = atanf(0.66) * 180 / 3.1416;
//	tan_my = tanf(my);
//	tan_sp = tanf(sp);
//	float rep;
//	rep = tan_my / tan_sp;
	printf("A sp %.2f A my %.2f\n", sp, my);
//	printf("TanMy [%.10f]\nTanSp [%.10f]\nRep   [%.10f]\n\n", tan_my, tan_sp, rep);
	printf("\033[31m%.2f\033[0m\n", jpp);
	dif += 33;
	dif /= 100;
	float test;
	test = 600 / a * (sp - a);
	printf("\033[32m%.2f\033[0m\n", test);
	perc = ((float)player->len_screen) / (float)0.66;
//	printf("Dif %.2f | perc %.2f\n", dif, perc);
	perc = perc * dif;

//	ft_printf("Col %i\n\n", (int)perc);
	if (perc > 0 && perc < e->width)
	{
		e->sprite[0].col = 600 + (int)test;
		float dist = (float)1 / ((float)33.333);
		dist = (float)dist * (float)(dif * 100) - (float)1;
		ray_dir.x = player->dir.x + (player->plan.x * dist);
		ray_dir.y = player->dir.y + (player->plan.y * dist);
//		printf("Raydir spri [%.2f][%.2f]\n\n\n", ray_dir.x, ray_dir.y);
		int lt = e->radar.lt;
		e->to.x1 = player->pos.x * lt;
		e->to.y1 = player->pos.y * lt;
		e->to.x2 = (player->pos.x + ray_dir.x) * lt;
		e->to.y2 = (player->pos.y + ray_dir.y) * lt;
		mlxji_draw_line(e->img, &e->to, 0x0FFFF0);
		if ((int)perc > 0 && (int)perc < e->width && e->side_touch[(int)perc] == 'x')
			e->sprite[0].dist = rela.x / ray_dir.x;
		else
			e->sprite[0].dist = rela.y / ray_dir.y;
//		e->sprite[0].dist = sqrt(pow(rela.x, 2) + pow(rela.y, 2));
//		int len_sprite = e->sprite[0].len_min / e->sprite[0].dist;
//		if ((int)perc + len_sprite >=0 || (int)perc - len_sprite < e->width)
			e->sprite[0].hit = 1;
	}
}
