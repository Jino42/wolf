/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:48:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/27 18:49:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "../libft/includes/libft.h"
#include "../libmlxji/includes/mlxji.h"
#include <stdio.h> ////////////
#include "mlx.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720

# define TEXT_X 64
# define TEXT_Y 64

# define B_VOID '0'
# define B_WALL '1'

# define F_AFF_BASIC (1 << 0)
# define F_3D (1 << 1)

# define COL_RED_SMOOTH 0xDC143C
# define COL_GREEN_SMOOTH 0x228B22
# define COL_GREEN_CLEAR 0x00FF7F
# define COL_ORANGE_CLEAR 0xD2691E
# define COL_MAP_2D 0x8B0000
# define COL_PLAYER_2D 0x00BFFF
# define COL_EN_2D 0xffa29f

# define TEX_MAX 1400

# define TEX_SKY 0

# define NB_TEX 2

# define NB_SPRITE 2

# define SIZE_REALLOC_MAP 10

typedef struct	s_tex
{
	unsigned char	*tex;
	int				width;
	int				height;
}				t_tex;

typedef struct	s_map
{
	char		**map;
	int			len_x;
	int			len_y;

}				t_map;

typedef struct	s_fvector2d
{
	float			x;
	float			y;
}				t_fvector2d;

typedef struct	s_ivector2d
{
	int			x;
	int			y;
}				t_ivector2d;

typedef struct	s_sprite
{
	t_fvector2d	pos;
	int			col;
	int			len_x;
	int			len_y;
	int			len_min;
	int			hit;
	float		dist;
	char		*sprite;
}				t_sprite;

typedef struct	s_ray
{
	t_map		*map;
	t_fvector2d	dir;

	float		dist_wall;
	float		percent_wall;
	t_fvector2d	end;
	t_fvector2d	start;
	int			hit;

	t_fvector2d	delta_len;
	t_fvector2d	len;
	int			step_x;
	int			step_y;
	int			side;
	t_ivector2d	pos_map;
}				t_ray;

typedef struct	s_player
{
	int				cart_pos_y;
	int				cart_pos_x;
	t_fvector2d		pos;
	t_fvector2d		dir;
	t_fvector2d		plan;
	float			angle;
	float			move_speed;
	float			rotate_speed;
	float			jump;
	int				len_screen;
}				t_player;

typedef struct	s_radar
{
	int			len_tile;
	int			len_tile_fs;
	int			lt;
	int			len_x;
	int			len_y;
}				t_radar;

typedef struct	s_fps
{
	struct timeval	step;
	struct timeval	cur;
	int				fps;
	int				ret_fps;
}				t_fps;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_px		col;
	int			icol;
	t_pxtopx	to;
	int			flag;

	int			height;
	int			width;

	int			key[269];

	float		dist[WIN_WIDTH + 10];//////
	t_fps		fps;
	t_map		map;
	t_radar		radar;
	t_player	player;
	t_tex		tex[NB_TEX];
	t_sprite	sprite[NB_SPRITE];
	t_fvector2d wall;
	t_fvector2d endw;
	int			size_side;
	int			size_half_side;
	int			rez;
}				t_env;

int				loop(t_env *e);

void			update_key_event(t_env *e);

void			move_player(t_env *e, int dir);

int				import_texture(t_env *e);
int				end_of_program(t_env *e, char *str);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

void			radar(t_env *e);
void			radar_full_screen(t_env *e);
void			raycast_wolf(t_env *e, t_player *player);

void			sprite_wolf(t_env *e, t_sprite *sprite, t_player *player);

int				raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);
void			init_raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);

void			sprite_search(t_env *e, t_player *player);

int				round_to_inf(float nb);
int				round_to_up(float nb);
int				ft_max(int a, int b);
int				ft_min(int a, int b);

int				mlxji_rgb_to_int(t_px *col);
void			mlxji_draw_case(t_img *img, t_pxtopx *px, int col);
void			mlxji_draw_y_line(t_img *img, t_pxtopx *to, int col);
void			mlxji_draw_x_line(t_img *img, t_pxtopx *to, t_px *px);
void			fvector_rotation(t_fvector2d *vec, float rotation);

void			init_var(t_env *e);
void			init_env(t_env *e);
int				init_map(t_env *e, char *s);

#endif
