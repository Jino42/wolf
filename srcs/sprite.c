/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:39:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 16:22:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
static void	set_sprite(t_env *e)
{
}
*/

void		sprite_wolf(t_env *e, t_sprite *sprite)
{
	int len_sprite;

	if (!sprite->hit)
		return ;

	float len;
	float len_pp;

	len_sprite = sprite->len_min / sprite->dist;
	e->to.x1 = (sprite->col - (len_sprite >> 1));
	e->to.x2 = (sprite->col + (len_sprite >> 1));
	e->to.y1 = (e->size_half_side - (len_sprite	>> 1));
	e->to.y2 = (e->size_half_side + (len_sprite >> 1));
	if (e->to.x2 >= e->width)
		e->to.x2 = e->width - 1;
	if (e->to.y1 < 0)
		e->to.y1 = 0;
//	if (e->to.y1 >= e->to.y2)
	//	return ;
	e->to.y2 = e->to.y1;
	len = 0;
	len_pp = len_sprite;
	len_pp /= ft_min(sprite->len_y, sprite->len_x);
	int i;
	int start_y = e->to.y1;
	int col;
	float x = 0;
	float len_xp = (float)ft_min(sprite->len_y, sprite->len_x) / len_sprite;
	while (e->to.x1 < e->to.x2)
	{
		if (e->to.x1 >= 0 && sprite->dist < e->dist[e->to.x1])
		{
			i = 0;
			len = 0;
			e->to.y2 = start_y;
			while (len < len_sprite)
			{
				e->to.y1 = e->to.y2;
				e->to.y2 = start_y + len;
				if (e->to.y2 >= e->height)
					break ;
				col = *((int *)&sprite->sprite[((int)x << 2) + i * (sprite->len_x << 2)]);
				//verif i y len
				mlxji_draw_y_line(e->img, &e->to, col);
				len += len_pp;
				i++;
			}
		}
		e->to.x1++;
		x += len_xp;
	}
}
