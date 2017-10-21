/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 20:55:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 20:55:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycast_aff_sky(t_env *e, int nb_cast, int end)
{
	int			i;
	int			text_x;
	t_pxtopx	to;
	int			icol;

	ft_bzero(&to, sizeof(t_pxtopx));
	to.x1 = nb_cast + 1;
	to.y2 = 0;
	i = 0;
	text_x = to.x1 + e->player.angle * 300;
	if (text_x < 0)
		text_x = e->tex[TEX_SKY].width - text_x;
	while (i < end)
	{
		to.y1 = to.y2;
		to.y2 = to.y1 + 1;
		icol = *((int *)&e->tex[TEX_SKY].tex[(text_x << 2) + i *
				(e->tex[TEX_SKY].width << 2)]);
		if (to.y2 >= e->size_side)
			to.y2 = e->size_side - 1;
		mlxji_draw_y_line(e->img, &to, icol);
		i++;
	}
}
