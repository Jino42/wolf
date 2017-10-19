/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 23:58:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		print_map(t_env *e)
{
	int i;

	ft_printf("_____________________________\n");
	i = 0;
	while (i < e->map.len_y)
	{
		ft_printf("%s\n", e->map.map[i]);
		i++;
	}
	ft_printf("_____________________________\n\n");
}

int			main(int argc, char **argv)
{
	t_env e;

	if (argc != 2)
		return (ft_ret_error("Miss Args\n"));
	init_env(&e);
	if (!(init_map(&e, argv[1])))
		return (0);
	print_map(&e);
	init_var(&e);
	if (!(import_texture(&e)))
		return (ft_ret_error("Erreur de textures\n")); //free
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	return (0);
}
