/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:48:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 22:15:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "../libft/includes/libft.h"
#include "../libmlxji/includes/mlxji.h"
#include "mlx.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define SIZE_REALLOC_MAP 10

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			flag;

	int			height;
	int			width;

	int			key[269];

	char		**map;
	int			len_x;
	int			len_y;

	int			pos_y;
	int			pos_x;
	int			angle;
	int			fov;
	int			dist_to_cam;
}				t_env;

int				loop(t_env *e);

int				end_of_program(t_env *e, char *str);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

#endif
