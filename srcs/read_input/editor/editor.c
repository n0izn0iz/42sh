# include <libft.h>
# include <term.h>
# include <termios.h>
# include <curses.h>

# include "utils.h"
# include "abstract_list.h"
# include "shell_env.h"

# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

#include "history.h"
#include "variable.h"

t_editor *get_editor()
{
	static t_editor ed;
	return (&ed);
}

t_editor	*init_editor()
{
	t_editor	*new;

	new = get_editor();
	ft_start_termcaps();
	new->term = init_term();
	ft_close_termcaps();
	new->history = get_shell_env()->history;
	new->prompt = gen_prompt();
	new->prompt_size = ft_strlen(new->prompt);
	list_goto_last((t_abstract_list **)&new->history);
	return (new);
}

void	add_to_string(t_editor *ed, char c)
{
	t_string *new;

	ed->need_refresh = true;
	new = memalloc_or_die(sizeof(t_string));
		new->c = c;

	if (!ed->string)
	{
		ed->string = new;
	}
	else
	{
		list_push_at_pos(ed->cursor_position, (t_abstract_list **)ed->string, (t_abstract_list *)new);
	}
	ed->cursor_position++;
}

void print_string(t_string *s)
{
	while (s)
	{
		ft_putchar(s->c);
		s = s->next;
	}
	// ft_putchar('\n');
}

char *get_string_from_list(t_string *s)
{
	char 	*str;
	size_t	i;

	str = memalloc_or_die(list_count((t_abstract_list*)s) + 1);
	i = 0;
	while (s)
	{

		str[i] = s->c;
		i++;
		s = s->next;
	}
	str[i] = '\0';
	return (str);
}

void free_string(t_string *s)
{
	while (s)
	{
		s = s->next;  //remove
	}
	free(s);
}

/////// OBSOLETTE FUNCTION //////////////
/////////////////////////////////////////
/////////////////////////////////////////
//USE THIS 
//t_editor *ed;
//ed->need_refresh == true;
/////////////////////////////////////////
void	ft_clear_line(t_string *s)
{
	char *move_left = tgetstr("le", NULL);

	while (s)
	{
		ft_putstr(move_left);
		s = s->next;
	}
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr(tgetstr("ce", NULL));
}
/////////////////////////////////////////
/////////////////////////////////////////
