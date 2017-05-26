#include "sig_handler.h"
#include "read_input/editor/editor.h"
#include "errno.h"
#include <sys/wait.h>
#include "read_input/event_callbacks/event_callback_def.h"

void		sig_int(int sig)
{
	t_editor	*ed;

	(void)sig;
	kill(-2, SIGKILL);
	ed = get_editor();
	if (ed->in_edition)
	{
		
		// Need quit quote prompt //

		if (get_shell_env()->last_unmatched)
			get_shell_env()->del_input = 1;
		get_shell_env()->last_unmatched = NO_ERROR;
		ev_cursor_end(ed);
		ft_putstr("^C\n");
		change_string(ed, "");
		ed->pos = get_cursor_vector(ed);
		ed->need_refresh = true;
		refresh_line(ed);
	}
	else
	{
		// ft_putstr("\n");
	}
}