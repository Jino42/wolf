/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:45:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 21:45:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		fvector_rotation(t_fvector2d *vec, float rotation)
{
	float tmp;

	tmp = vec->x * cos(rotation) - vec->y * sin(rotation);
	vec->y = vec->y * cos(rotation) + vec->x * sin(rotation);
	vec->x = tmp;
}
