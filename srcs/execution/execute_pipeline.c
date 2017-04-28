#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"
#include "pipe.h"
#include "exec.h"
#include <stdio.h>
#include "redirection.h"
#include "expansion/expansion.h"
#include "errno.h"
#include <signal.h>

t_error_id	execute_file(t_simple_command *cmd, size_t lvl)
{
	t_error_id	ret;

	(void)lvl;
	if (cmd->argv[0] == NULL)
		fatal_error("NULL argv[0] fed to execute_file");
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "executing file %s\n", cmd->argv[0]);
#endif
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		pre_exec(cmd);
#ifdef FTSH_DEBUG
		print_n_char_fd(' ', (lvl + 1) * 2, 2);
#endif
		print_errno_error(errno, cmd->argv[0], NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait_for_childs();
		if (cmd->argv && cmd->argv[0])
			set_variable("_", cmd->argv[ft_tablen(cmd->argv) - 1], false);
		else
		{
			set_assignments(cmd->assignments, false);
			set_variable("_", NULL, false);
		}
		ret = get_last_exit_status();
	}
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "done executing file %s, %s\n", cmd->argv[0], ret == NO_ERROR ? "ok" : "error");
#endif
	return (ret);
}

t_error_id	execute_simple_command(t_simple_command *cmd, size_t lvl)
{
	t_error_id	ret;
	int			*stdin_out_backup;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
#ifdef FTSH_DEBUG
		print_n_char_fd(' ', (lvl) * 2, 2);
		dprintf(2, "executing simple command %s\n", cmd->argv[0]);
		// EXECUTION CORE
		print_n_char_fd(' ', (lvl + 1) * 2, 2);
		dprintf(2, "expanding simple command %s\n", cmd->argv[0]);
#endif
		expand_cmd_words(&cmd->argv);
#ifdef FTSH_DEBUG
		print_n_char_fd(' ', (lvl + 1) * 2, 2);
		dprintf(2, "done expanding simple command %s\n", cmd->argv[0]);
#endif
		stdin_out_backup = save_stdin_stdout();
		ret = redirect(cmd->redirections, stdin_out_backup);
		//expand_assignments_values(cmd->assignments);
		if (ret != NO_ERROR || cmd->argv[0] == NULL)
			return (ret);
		ret = execute_builtin(cmd, lvl + 1);
		if (ret == NO_SUCH_BUILTIN)
			ret = execute_file(cmd, lvl + 1);
		restore_stdin_stdout(stdin_out_backup);
#ifdef FTSH_DEBUG
		print_n_char_fd(' ', (lvl) * 2, 2);
		dprintf(2, "done executing simple command %s, %s\n", cmd->argv[0], ret == NO_ERROR ? "ok" : "error");
#endif
	}
	return (ret);
}

t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl)
{
	t_error_id			ret;
	t_pipeline_state	pipeline_state;

	if (pipeline == NULL)
		return (NO_ERROR);
	if (pipeline->next == NULL)
		return (execute_simple_command(pipeline, lvl));
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "executing pipeline\n");
#endif
	ft_bzero(&pipeline_state, sizeof(t_pipeline_state));
	ret = NO_ERROR;
	while (pipeline != NULL)
	{
		if (pipeline->next == NULL)
			pipeline_state.last_cmd = true;
		if (pipe_me_in(&pipeline_state) == FORKED_IN_CHILD)
		{
			ret = execute_simple_command(pipeline, lvl + 1);
			if (ret == NO_ERROR)
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		pipeline = pipeline->next;
	}
	wait_for_last_child(pipeline_state.last_pid);
	kill(0, SIGINT);
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "done executing pipeline, %s\n", pipeline_state.last_ret == NO_ERROR ? "ok" : "error");
#endif
	return (ret);
}
