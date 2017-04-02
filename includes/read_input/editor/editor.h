#ifndef EDITOR_H
# define EDITOR_H

# include "read_input/editor/editor_struct.h"
# include "vec2i.h"

t_editor	*init_editor();
t_editor 	*get_editor();
void		add_to_string(t_editor *ed, char c);
char		*get_string_from_list(t_string *s);
void		free_string(t_string *s);
char		*gen_prompt(void);
t_vec2i		get_cursor_vector(t_editor *ed);
void		move_cursor(t_vec2i	vec, t_term *term);
t_vec2i		vec2i_sub(t_vec2i a, t_vec2i b);

void		clear_line(t_editor *ed);
void		put_line(t_editor *ed);
void		move_start(t_editor *ed);
void		refresh_line(t_editor *ed);
void		free_editor(t_editor *ed);

void		put_highlighted_line(t_editor *ed, char* line);
void		swap_position_if_needed(t_editor *ed);
void		clear_selected_pos(t_editor *ed);

size_t		find_index_at_vector(t_editor *ed, int ox, int oy);
t_vec2i		get_cursor_vector(t_editor *ed);
bool		if_on_multiline(t_editor *ed);

#endif
