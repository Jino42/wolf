/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/25 22:25:13 by ntoniolo         ###   ########.fr       */
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
	int	height_half_wall;

	if (!sprite->hit)
		return ;
	(void)player;
	height_half_wall = (int)((float)e->size_side /  2);
	e->to.x1 = sprite->col - sprite->len_x / 2;
	e->to.x2 = sprite->col + sprite->len_x / 2;
	e->to.y1 = height_half_wall - sprite->len_y / 2;
	e->to.y2 = height_half_wall + sprite->len_y / 2;
	int x = 0, y = 0;
	while (x < sprite->len_x)
	{
		e->to.y1 = height_half_wall - sprite->len_y / 2;
		printf("%.2f < %.2f (%i)\n", sprite->dist,
					e->dist[(sprite->col - sprite->len_x + x)],
					(sprite->col - sprite->len_x + x));
		if (sprite->dist < e->dist[(sprite->col - sprite->len_x + x)])
		{
			y= 0;
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
