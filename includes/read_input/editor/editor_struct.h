#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

# include "shell_env.h"
# include <stdbool.h>

typedef struct			s_string
{
	struct s_string		*next;
	struct s_string		*prev;  // not link !!!!!!!!!!!!!!!
	char				c;
}						t_string;

typedef struct			s_term
{
	int					width;
	char				*move_cursor_begining;
	char				*move_left;
	char				*move_right;
	char				*hide_cursor;
	char				*show_cursor;
}						t_term;

typedef struct			s_editor
{
	t_string			*string;
	t_term				*term;
	t_history			*history;
	int					cursor_position;
	int					string_size;
	bool				need_refresh;
}						t_editor;

#endif
