#include "vec2i.h"

t_vec2i		vec2i_sub(t_vec2i a, t_vec2i b)
{
	t_vec2i	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}
