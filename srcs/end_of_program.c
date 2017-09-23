/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:31:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/23 18:09:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		free_env(t_env *e)
{
	int i;

	i = 0;
	while (i < NB_TEX)
	{
		ft_strdel((void *)&e->tex[i].tex);
		i++;
	}
}

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
	free_env(e);
	if (str)
		ft_putstr_fd(str, 2);
	return (0);
}
