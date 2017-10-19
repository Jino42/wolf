/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_limit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:44:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 21:44:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		fvector2d_limit(t_fvector2d *a, const float limit)
{
	if (fvector2d_magnitude(*a) > limit)
	{
		fvector2d_normalize(a);
		a->x *= limit;
		a->y *= limit;
	}
	return ;
}
