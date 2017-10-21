/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 22:48:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			main(int argc, char **argv)
{
	t_env e;

	if (argc != 2)
		return (ft_ret_error("usage: ./wolf3d [file]\n"));
	init_env(&e);
	if (!(init_map(&e, argv[1])))
		return (0);
	init_var(&e);
	if (!(import_texture(&e)))
		return (end_of_program(&e, "Erreur de textures\n"));
	init_mlx(&e);
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	return (0);
}
