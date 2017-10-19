/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:01:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 21:03:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float	fvector2d_distance(t_fvector2d a, t_fvector2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (fvector2d_magnitude(a));
}
