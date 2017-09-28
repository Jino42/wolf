/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:22:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:06:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			round_to_inf(float nb)
{
	return ((int)nb);
}

int			round_to_up(float nb)
{
	return ((int)nb + 1);
}

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

void		fvector_rotation(t_fvector2d *vec, float rotation)
{
	float tmp;

	tmp = vec->x * cos(rotation) - vec->y * sin(rotation);
	vec->y = vec->y * cos(rotation) + vec->x * sin(rotation);
	vec->x = tmp;
}
