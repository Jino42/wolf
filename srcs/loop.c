/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/23 23:13:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Glissement sur MUR ! Car deux etape
**Besoin de voir Sin Cos omgbb
*/

void		update_fps(t_fps *fps)
{
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

void		sprite_wolf(t_env *e, t_sprite *sprite, t_player *player)
{
	t_fvector2d	d;

	int lt;

	lt = e->radar.len_tile;
	(void)e;
	d.x = sprite->pos.x - player->pos.x;
	d.y = sprite->pos.y - player->pos.y;
	float inv = 1 / (player->plan.x * player->dir.y - player->dir.x * player->plan.y);
	t_fvector2d test;

	test.x = inv * (d.x * player->dir.y - d.y * player->dir.x);
	test.y = inv * (d.x * -player->plan.y + d.y * player->plan.x);
	printf("[%.2f][%.2f]\n", test.x / test.y, test.y);
	t_pxtopx to;

	to.x1 = (e->player.len_screen / 2) * (test.x / test.y) + (e->player.len_screen / 2)- 5;
	// / 2 car mid plan_x
	to.x2 = to.x1 + 5;
	to.y1 = e->height / 2 + 5;
	to.y2 = e->height / 2 - 5;
	if (to.x1 < e->width - 10)
		mlxji_draw_case(e->img, &to, COL_EN_2D);
	int lx, ly;
	lx= player->plan.x + player->dir.x;
	ly= player->plan.y + player->dir.y;
	to.x1 = (test.x+lx) * lt - 5;
	to.x2 = (test.x+lx) * lt + 5;
	to.y1 = (test.y+ly) * lt + 5;
	to.y2 = (test.y+ly) * lt - 5;
	if (to.x1 < e->width - 10)
		mlxji_draw_case(e->img, &to, COL_EN_2D);
}

int			loop(t_env *e)
{
	update_fps(&e->fps);
	update_key_event(e);
	ft_bzero(e->img->data, e->height * e->width * 4);
	raycast_wolf(e, &e->player);
	radar(e);
	sprite_wolf(e, &e->sprite, &e->player);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
