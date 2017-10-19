/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:56:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 21:00:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		fvector2d_normalize(t_fvector2d *vec)
{
	float magnitude;

	magnitude = fvector2d_magnitude(*vec);
	vec->x = vec->x / magnitude;
	vec->y = vec->y / magnitude;
}
