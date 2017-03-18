#ifndef EVENT_CALLBACK
# define EVENT_CALLBACK

# include "read_input/editor/editor.h"

# define EV_CB_RET void
# define EV_CB_ARGS t_editor *ed

typedef EV_CB_RET	(*t_event_callback)(EV_CB_ARGS);

EV_CB_RET 	event_cursor_right(EV_CB_ARGS);
EV_CB_RET 	event_newline(EV_CB_ARGS);
EV_CB_RET 	event_cursor_left(EV_CB_ARGS);
EV_CB_RET 	event_cursor_right(EV_CB_ARGS);
EV_CB_RET 	event_cursor_up(EV_CB_ARGS);
EV_CB_RET 	event_cursor_down(EV_CB_ARGS);
EV_CB_RET 	event_cursor_home(EV_CB_ARGS);
EV_CB_RET 	event_cursor_end(EV_CB_ARGS);
EV_CB_RET 	event_cursor_word_right(EV_CB_ARGS);
EV_CB_RET 	event_cursor_word_left(EV_CB_ARGS);
EV_CB_RET 	event_history_up(EV_CB_ARGS);
EV_CB_RET 	event_history_down(EV_CB_ARGS);
EV_CB_RET 	event_copy(EV_CB_ARGS);
EV_CB_RET 	event_cut(EV_CB_ARGS);
EV_CB_RET 	event_paste(EV_CB_ARGS);
EV_CB_RET 	event_cancel(EV_CB_ARGS);
EV_CB_RET 	event_exit(EV_CB_ARGS);
EV_CB_RET 	event_delete(EV_CB_ARGS);

void	restore_old_cursor_position(t_editor *ed, int old_position);

#endif
