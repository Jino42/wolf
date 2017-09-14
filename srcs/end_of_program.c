/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:31:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 19:35:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		free_mlx(t_env *e)
{
	if (!e || !e->img)
		return ;
	if (e->mlx && e->img)
		mlx_destroy_image(e->mlx, e->img->img);
	if (e->mlx && e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e->img)
		free(e->img);
}

int				end_of_program(t_env *e, char *str)
{
	free_mlx(e);
	if (str)
		ft_putstr_fd(str, 2);
	return (0);
}