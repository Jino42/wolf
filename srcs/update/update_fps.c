/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:22:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 18:30:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		update_fps(t_env *e, t_fps *fps)
{
	gettimeofday(&fps->step2, NULL);
	if (e->s)
	{
		e->time_frame = (float)(fps->step2.tv_usec - fps->cur.tv_usec)
													/ 1000000;
		if (e->time_frame < 0.005)
			e->time_frame = 0.005;
		if (fps->cur.tv_sec != fps->step2.tv_sec)
			e->time_frame = (float)(fps->step2.tv_usec +
								(1000000 - fps->cur.tv_usec)) / 1000000;
	}
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
		ft_printf("FPS [%i]\n", fps->ret_fps);
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
		e->s++;
	}
	fps->fps++;
}
