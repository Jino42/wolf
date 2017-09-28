/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_aequals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:22:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 22:26:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char		fvector2d_aequals(t_fvector2d a, t_fvector2d b)
{
	if (fabs(fvector2d_magnitude(a) - fvector2d_magnitude(b)) < 0.00005)
		return (1);
	return (0);
}
