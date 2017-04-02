#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

# include "shell_env.h"
# include <stdbool.h>
# include "vec2i.h"

typedef struct			s_string
{
	struct s_string		*next;
	char				c;
}						t_string;

typedef struct			s_term
{
	int					width;
	char				*move_cursor_begining;
	char				*move_left;
	char				*move_right;
	char				*move_up;
	char				*move_down;
	char				*hide_cursor;
	char				*show_cursor;
	char				*clear_line;
}						t_term;

typedef struct			s_editor
{
	bool				in_selection;
	bool				selected;
	size_t				selected_string_start;
	size_t				selected_string_end;
	char				*selected_string;
	t_string			*string;
	char				*string_cstr;
	char				**string_split;
	t_term				*term;
	t_history			*history;
	size_t				old_position;
	t_vec2i				pos;
	size_t				cursor_position;
	size_t				string_size;
	size_t				prompt_size;
	char				*prompt;
	bool				need_refresh;
	bool				action_move_left;
}						t_editor;

#endif
