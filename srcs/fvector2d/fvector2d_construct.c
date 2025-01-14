/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:44:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 21:44:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_fvector2d		fvector2d_construct(float x, float y)
{
	t_fvector2d new;

	new.x = x;
	new.y = y;
	return (new);
}
