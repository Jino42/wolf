/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:22:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/20 16:17:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int			ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void		t_pxtopx_limit_map(t_env *e, t_pxtopx *to)
{
	if (to->x1 < 0)
		to->x1 = 0;
	if (to->x2 < 0)
		to->x2 = 0;
	if (to->y1 < 0)
		to->y1 = 0;
	if (to->y2 < 0)
		to->y2 = 0;
	if (to->y2 >= e->height)
		to->y2 = e->height -1;
	if (to->y1 >= e->height)
		to->y1 = e->height -1;
	if (to->x2 >= e->width)
		to->x2 = e->width -1;
	if (to->x1 >= e->width)
		to->x1 = e->width -1;
	return ;
}
