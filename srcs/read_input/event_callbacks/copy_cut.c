# include "event_callback_def.h"
# include <libft.h>
# include "abstract_list.h"

static void	get_sub_string(EV_CB_ARGS)
{
	char	*all;
	size_t	start;
	size_t	end;

	start = ed->selected_string_start;
	end = ed->selected_string_end;
	all = get_string_from_list(ed->string);
	free(ed->selected_string);
	ed->selected_string = ft_strsub(all, start, end - start);
	free(all);
}

static void delete_selected(EV_CB_ARGS)
{
	ed->cursor_position = ed->selected_string_end;
	while (ed->cursor_position > ed->selected_string_start)
		event_delete(ed);
}

static void	get_position(EV_CB_ARGS)
{
	if (!ed->in_selection)
	{
		ed->selected = false;
		ed->in_selection = true;
		ed->selected_string_start = ed->cursor_position;
	}
	else
	{
		ed->in_selection = false;
		ed->selected_string_end = ed->cursor_position;
		ed->selected = true;
		swap_position_if_needed(ed);
	}
}

EV_CB_RET	event_copy(EV_CB_ARGS)
{
	if (if_on_multiline(ed))
		return ;
	get_position(ed);
	if (ed->selected)
	{
		get_sub_string(ed);
		clear_selected_pos(ed);
	}
	ed->string_size = list_count((t_abstract_list *)ed->string);
}

EV_CB_RET	event_cut(EV_CB_ARGS)
{
	if (if_on_multiline(ed))
		return ;
	get_position(ed);
	if (ed->selected)
	{
		get_sub_string(ed);
		delete_selected(ed);
		clear_selected_pos(ed);
	}
	ed->string_size = list_count((t_abstract_list *)ed->string);
}
