/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/26 15:36:02 by ntoniolo         ###   ########.fr       */
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
	int	height_half_sprite;

	if (!sprite->hit)
		return ;
	(void)player;
	printf("Col %i\n [%.2f][%.2f]", sprite->col, sprite->dist, e->dist[sprite->col]);
	height_half_sprite = (sprite->len_x / sprite->dist / 2);
	int len_sprite = height_half_sprite * 2;
	e->to.x1 = (sprite->col - height_half_sprite);
	e->to.x2 = (sprite->col + height_half_sprite);
	e->to.y1 = (e->size_half_side - height_half_sprite);
	e->to.y2 = (e->size_half_side + height_half_sprite);
	int x = 0, y = 0;
	if (e->to.x1 < 0)
		e->to.x1 = 0;
	if (e->to.y1 < 0)
		e->to.y1 = 0;
	if (e->to.y2 >= e->height)
		e->to.y2 = e->height - 1;
	if (e->to.x2 >= e->width)
		e->to.x2 = e->width - 1;
	if (e->to.y1 >= e->to.y2 || e->to.x1 >= e->to.x2)
		return ;
	while (e->to.x1 < e->to.x2)
	{
		e->to.y1 = (e->size_half_side - height_half_sprite);
		if (e->to.y1 < 0)
			e->to.y1 = 0;
		if ((sprite->col - len_sprite + x) > 0 && (sprite->col - len_sprite + x) < e->player.len_screen && sprite->dist < e->dist[(sprite->col - len_sprite + x)]) //mais plus base sur len_x
		{
			y = 0;
			mlxji_draw_y_line(e->img, &e->to, 0x00FF00);
		}
		x++;
		e->to.x1++;
	}
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
