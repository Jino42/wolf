/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:31:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 23:00:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				end_of_program(t_env *e, char *str)
{
	free_mlx(e);
	free_env(e);
	if (str)
		ft_putstr_fd(str, 2);
	return (0);
}
