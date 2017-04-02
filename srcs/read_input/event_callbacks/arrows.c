# include "event_callback_def.h"
# include <libft.h>

void		move_cursor(t_vec2i	vec, t_term *term)
{
	if (vec.x > 0)
	{
		while (vec.x-- > 0)
			ft_putstr(term->move_left);
	}
	else if (vec.x < 0)
	{
		while (vec.x++ < 0)
			ft_putstr(term->move_right);
	}
	if (vec.y > 0)
	{
		while (vec.y-- > 0)
			ft_putstr(term->move_up);
	}
	else if (vec.y < 0)
	{
		while (vec.y++ < 0)
			ft_putstr(term->move_down);
	}
}

static void	cursor_left_core(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	if (ed->cursor_position > 0)
	{
		cursor_vec = get_cursor_vector(ed);
		ed->cursor_position--;
		mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
		move_cursor(mov_vec, ed->term);
	}
}

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	cursor_left_core(ed);
	if (ed->cursor_position == 0)
	{
		ed->need_refresh = true;
	}
	else
	{
		cursor_left_core(ed);
		event_cursor_right(ed);
	}
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	ed->need_refresh = true;
	if (ed->cursor_position < ed->string_size)
	{
		ed->cursor_position++;
	}
}

void move_cursor_to(t_vec2i old_pos, t_vec2i new_pos, t_term *term)
{
	move_cursor(vec2i_sub(old_pos, new_pos), term);
}

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{
	t_vec2i pos;

	if (if_on_multiline(ed))
		return ;

	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y - 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{
	t_vec2i pos;

	if (if_on_multiline(ed))
		return ;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y + 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
}
