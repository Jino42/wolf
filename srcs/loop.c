/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/26 23:02:53 by ntoniolo         ###   ########.fr       */
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
	float len;
	float len_pp;
	int len_sprite;
   
	len_sprite = ft_min(sprite->len_y, sprite->len_x) / sprite->dist;
	height_half_sprite = len_sprite / 2;
	e->to.x1 = (sprite->col - height_half_sprite);
	e->to.x2 = (sprite->col + height_half_sprite);
	e->to.y1 = (e->size_half_side - height_half_sprite);
	e->to.y2 = (e->size_half_side + height_half_sprite);
	if (e->to.x1 < 0)
		e->to.x1 = 0;
	if (e->to.x2 >= e->width)
		e->to.x2 = e->width - 1;
	if (e->to.y1 < 0)
		e->to.y1 = 0;
	if (e->to.y1 >= e->to.y2 || e->to.x1 >= e->to.x2)
		return ;
	int status = sprite->col - len_sprite / 2 - 1;
	e->to.y2 = e->to.y1;
	len = 0;
	len_pp = len_sprite;
//	printf("Dist %.2f\n", sprite->dist);
	len_pp /= ft_min(sprite->len_y, sprite->len_x);
	int i;
	int start_y = e->to.y1;
	int col;
    float x = 0;
	float len_xp = (float)ft_min(sprite->len_y, sprite->len_x) / len_sprite;
	while (e->to.x1 < e->to.x2)
	{
		if (status > 0 && status < e->player.len_screen && sprite->dist < e->dist[status]) //mais plus base sur len_x
		{
			i = 0;
			len = 0;
			e->to.y2 = start_y;
			while (i < ft_min(sprite->len_y, sprite->len_x))
			{
				e->to.y1 = e->to.y2;
				e->to.y2 = start_y + len;
				if (e->to.y2 >= e->height)
					e->to.y2 = e->height - 1;
				col = *((int *)&sprite->sprite[((int)x << 2) + i * (sprite->len_x << 2)]);
					mlxji_draw_y_line(e->img, &e->to, col);
				len += len_pp;
				i++;
			}
		}
		status++;
		e->to.x1++;
		x += len_xp;
	}
}

int			loop(t_env *e)
{
	update_fps(&e->fps);
	update_key_event(e);
	ft_bzero(e->img->data, e->height * e->width * 4);
	raycast_wolf(e, &e->player);
	radar(e);
	sprite_wolf(e, &e->sprite[0], &e->player);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
