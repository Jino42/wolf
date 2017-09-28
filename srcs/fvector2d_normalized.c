/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvector2d_normalized.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:53:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 20:56:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_fvector2d		fvector2d_normalized(t_fvector2d vec)
{
	t_fvector2d new;

	new.x = vec.x / fvector2d_magnitude(vec);
	new.y = vec.y / fvector2d_magnitude(vec);
	return (new);
}
