/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:48:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 20:08:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO
	-CLEAN
	-MAKE FINAL TEX
	-LEAKS
	-CLEAN
	-REVI
	-PUSH
TODO
*/




#ifndef WOLF_H
# define WOLF_H

#include "../libft/includes/libft.h"
#include "../libmlxji/includes/mlxji.h"
#include <stdio.h> ////////////
#include <pthread.h>
#include "mlx.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
# include <stdbool.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720

# define B_VOID '0'
# define B_WALL '1'

# define F_AFF_BASIC (1 << 0)
# define F_3D (1 << 1)

# define SP_GRAVITY (1 << 10)

# define COL_RED_SMOOTH 0xDC143C
# define COL_GREEN_SMOOTH 0x228B22
# define COL_GREEN_CLEAR 0x00FF7F
# define COL_ORANGE_CLEAR 0xD2691E
# define COL_MAP_2D 0x8B0000
# define COL_PLAYER_2D 0x00BFFF
# define COL_EN_2D 0xffa29f

# define TEX_MAX 1400

# define TEX_SKY 0

# define NB_TEX 6

# define NB_SPRITE 2

# define ITEM_SEGFAULT -1

# define SIZE_REALLOC_MAP 10

# define NB_THREAD 4

typedef struct	s_tool_sprite
{
	float		len_y;
	float		len_pp_y;
	float		len_pp_x;
	float		x;
	int			len_sprite_y;
	int			len_sprite_x;
	int			i;
	int			start_y;
	int			col;
}				t_ts;

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
	t_fvector2d	rela;
	t_fvector2d	ray_dir;
	t_fvector2d dir;
	t_fvector2d acceleration;
	t_fvector2d velocity;
	int			item;
	int			spe_angle;
	int			col;
	int			len_x;
	int			len_y;
	int			len_min;
	int			hit;
	float		dist;
	t_tex		*sprite;
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
	int			get;
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
	struct timeval	step2;
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
	pthread_mutex_t mutex;
	int			flag;

	int			height;
	int			width;

	int			key[269];

	float		dist[WIN_WIDTH + 10];
	int			apply[WIN_WIDTH + 10];
	t_ray		ray;
	t_fps		fps;
	float		time_frame;
	t_map		map;
	t_radar		radar;
	t_player	player;
	t_tex		tex[NB_TEX];
	t_list		*sprite;
	t_btree		*sprite_aff;
	t_tex		tex_sprite[NB_SPRITE];
	//t_sprite	sprite[NB_SPRITE];
	t_fvector2d	ray_end[WIN_WIDTH + 10];
	int			size_side;
	int			size_half_side;
	long		s;
}				t_env;

typedef struct		s_ptr_env
{
	t_env 			*e;
	t_player		*player;
	float			start;
	float			end;
	int				nb;
}					t_ptr_env;

int				loop(t_env *e);

void			update_key_event(t_env *e);
void			update_sprite_position(t_env *e);
void 			update_fps(t_env *e, t_fps *fps);


void			move_player(t_env *e, int dir);

int				import_texture(t_env *e);
int				end_of_program(t_env *e, char *str);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

void			radar(t_env *e);
void			radar_full_screen(t_env *e);
void			raycast_wolf(t_env *e, t_player *player);
void			raycast_wolf_ar(t_env *e, t_player *player);

void			sprite_wolf(void *e, void  *sprite);

int				raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);
void			init_raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);

int				round_to_inf(float nb);
int				round_to_up(float nb);
int				ft_max(int a, int b);
int				ft_min(int a, int b);

void			fvector_rotation(t_fvector2d *vec, float rotation);

void			event_fire(t_env *e, t_player *player);

void			init_var(t_env *e);
void			init_env(t_env *e);
int				init_map(t_env *e, char *s);

void			sprite_hit(t_env *e, t_ray *ray, int s_screen);

void			raycast_aff(t_env *e, t_ray *ray, int nb_cast);
void  			raycast_aff_view_2d(t_env *e, t_player *player);
void			raycast_aff_floor(t_env *e, int nb_cast, int start);
void			raycast_aff_sky(t_env *e, int nb_cast, int end);
void			raycast_aff_basic(t_env *e, int nb_cast, int start_y, int end_y);
void			raycast_aff_tex(t_env *e, int nb_cast,
					int start_y, float len_pp, t_ray *ray);

float			fvector2d_magnitude(t_fvector2d vec);
float			fvector2d_distance(t_fvector2d a, t_fvector2d b);
t_fvector2d		fvector2d_normalized(t_fvector2d vec);
void			fvector2d_normalize(t_fvector2d *vec);
char			fvector2d_aequals(t_fvector2d a, t_fvector2d b);
void			fvector2d_limit(t_fvector2d *a, const float limit);
t_fvector2d		fvector2d_construct(float x, float y);

#endif
