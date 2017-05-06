#include "expansion.h"
#include "break_input/substitution.h"
#include <stdlib.h>
#include <libft.h>
#include "strlist.h"
#include "utils.h"
#include "errors.h"
#include "execution/exec.h"
#include "execution/pipe.h"
#include <stdio.h>
#include "shell_env.h"
#include "abstract_list.h"
#include "break_input/quoting.h"
#include "read_input/command_substitution.h"

static void		if_fork_in_child(t_strlist **strlist_addr, int pipefds[2])
{
	char				*tmp;

	close(pipefds[1]);
	tmp = fd_to_str(pipefds[0]);
	rm_trailing_newlines(tmp);
	strlist_append(strlist_addr, tmp);
	free(tmp);
	wait_for_children();
}

static void		add_substitution(t_strlist **strlist_addr
										, char const *start, char const *end)
{
	int					pipefds[2];
	char				**argv;
	t_simple_command	cmd;

	argv = (char*[]){ft_strdup(get_shell_env()->path_to_42sh), "-c"
											, strdup_until(start, end), NULL};
	pipe(pipefds);
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO);
		close(pipefds[1]);
		ft_bzero(&cmd, sizeof(t_simple_command));
		cmd.argv = argv;
		pre_exec(&cmd);
		fatal_error("failed to execute recursively in add_substitution");
	}
	else
		if_fork_in_child(strlist_addr, pipefds);
	free(argv[0]);
	free(argv[2]);
}

t_strlist		*split_subsitutions(char const *word)
{
	char const	*passv_str_start;
	char const	*subst_end;
	t_strlist	*result;
	char		quoted;

	quoted = 0;
	passv_str_start = NULL;
	result = NULL;
	while (*word != '\0')
	{
		if (is_quote(*word))
		{
			handle_quotes(*word, &quoted);
			if (passv_str_start == NULL)
				passv_str_start = word;
			if (*word == '\\' && *(word + 1) == '`')
				word++;
			word++;
		}
		else if (is_substitution_start(word) && \
			(!(quoted & IS_QU_SIMPLE) || (quoted & IS_QU_DOUBLE)))
		{
			if (passv_str_start != NULL)
				add_passive_string(&result, passv_str_start, word);
			subst_end = find_substitution_end(word + 1);
			add_substitution(&result, word + 1, subst_end);
			word = subst_end + 1;
			passv_str_start = word;
		}
		else
		{
			if (passv_str_start == NULL)
				passv_str_start = word;
			word++;
		}
	}
	if (passv_str_start != NULL)
		add_passive_string(&result, passv_str_start, word);
	return (result);
}
