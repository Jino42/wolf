#include "wolf.h"

t_fvector2d		fvector2d_construct(float x, float y)
{
	t_fvector2d new;

	new.x = x;
	new.y = y;
	return (new);
}
