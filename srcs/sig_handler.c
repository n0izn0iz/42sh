#include "sig_handler.h"
#include "read_input/editor/editor.h"
#include "errno.h"
#include <sys/wait.h>
#include <stdio.h>

#include "read_input/event_callbacks/event_callback_def.h"

// void		sig_int(int sig)
// {
// 	t_editor	*ed;

// 	(void)sig;
// 	ed = get_editor();
// 	kill(-2, SIGKILL);
// 	if (ed->in_edition == true)
// 	{
// 		ev_cursor_end(ed);
// 		change_string(ed, "");
// 		fflush(stdout);
// 		ft_putstr("^C\n");
// 		put_line(ed);
// 	}
// }

void		sig_int(int sig)
{
	t_editor	*ed;

	(void)sig;
	kill(-2, SIGKILL);
	ed = get_editor();
	if (ed->in_edition)
	{
		if (get_shell_env()->last_unmatched)
			get_shell_env()->del_input = 1;
		get_shell_env()->last_unmatched = NO_ERROR;
		change_string(ed, "");
		ft_putchar('\n');
		ed->need_refresh = true;
		refresh_line(ed);
	}
}