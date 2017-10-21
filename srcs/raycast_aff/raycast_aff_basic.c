/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 20:35:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 21:11:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycast_aff_basic(t_env *e, int start_y, int end_y, t_ray *ray)
{
	t_pxtopx to;

	ft_bzero(&to, sizeof(t_pxtopx));
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	to.x1 = (ray->x_screen + 1);
	to.y1 = start_y;
	to.x2 = (ray->x_screen + 1);
	to.y2 = end_y;
	if (ray->side == 'x')
	{
		if (ray->step_x == 1)
			mlxji_draw_y_line(e->img, &to, 0xf46242);
		else
			mlxji_draw_y_line(e->img, &to, 0xaff441);
	}
	else
	{
		if (ray->step_y == 1)
			mlxji_draw_y_line(e->img, &to, 0x41dff4);
		else
			mlxji_draw_y_line(e->img, &to, 0x9141f4);
	}
}
