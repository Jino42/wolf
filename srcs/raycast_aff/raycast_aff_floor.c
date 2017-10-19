#include "wolf.h"

void	raycast_aff_floor(t_env *e, int nb_cast, int start)
{
	t_pxtopx	to;

	to.x1 = nb_cast + 1;
	to.y1 = start - 1;
	to.y2 = e->height - 1;
	mlxji_draw_y_line(e->img, &to, 0);
}
