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

char					*strlist_to_str(t_strlist const *list)
{
	char	*result;

	result = NULL;
	while (list != NULL)
	{
		result = ft_strjoinf(result, list->str, 1);
		list = list->next;
	}
	return (result);
}

static void					add_passive_string(t_strlist **strlist_addr
										, char const *start, char const *end)
{
	char	*tmp;

	tmp = strdup_until(start, end);
	strlist_append(strlist_addr, tmp);
	free(tmp);
}

static char					*fd_to_str(int fd)
{
	size_t const	bufsz = 4096;
	char			buffer[bufsz];
	t_strlist		*list;
	int				ret;
	char			*result;

	list = NULL;
	while ((ret = read(fd, buffer, bufsz - 1)) > 0)
	{
		buffer[ret] = '\0';
		strlist_append(&list, buffer);
	}
	result = strlist_to_str(list);
	strlist_delete(&list);
	return (result);
}

static void					rm_trailing_newlines(char *str)
{
	size_t	len;
	len = ft_strlen(str);
	while (len-- > 0 && str[len] == '\n')
		str[len] = '\0';
}

static void					add_substitution(t_strlist **strlist_addr
										, char const *start, char const *end)
{
	int					pipefds[2];
	char				**argv;
	char				*tmp;
	char				*spath;
	char				**path;
	char				**env;

	argv = (char*[]){ft_strdup(get_shell_env()->path_to_42sh), "-c"
											, strdup_until(start, end), NULL};
	pipe(pipefds);
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO);
		close(pipefds[1]);
		spath = get_variable("PATH");
		path = ft_strsplit(spath, ':');
		ft_strdel(&spath);
		env = get_variables_for_execution(NULL);
		execute(argv, env, path);
		ft_freetabchar(path);
		ft_freetabchar(env);
		fatal_error("failed to execute recursively in add_substitution");
	}
	else
	{

		close(pipefds[1]);
		tmp = fd_to_str(pipefds[0]);

		rm_trailing_newlines(tmp);
		strlist_append(strlist_addr, tmp);
		free(tmp);
		wait_for_childs();
	}
	free(argv[0]);
	free(argv[2]);
}

static t_strlist			*split_subsitutions(char const *word)
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
			handle_quotes(*word, &quoted);
		if (is_substitution_start(word) && \
			(!(quoted & IS_QU_SIMPLE) || (quoted & IS_QU_DOUBLE)))
		{
			if (passv_str_start != NULL)
				add_passive_string(&result, passv_str_start, word);
			subst_end = find_substitution_end(word + 1);
			if (get_error() != NO_ERROR)
				// same as quotes - go back to read_input
				fatal_error("substitution end not found in split_subsitutions(), a substitution hasn't been correctly recognized before being expanded");
			add_substitution(&result, word + 1, subst_end);
			if (get_error() != NO_ERROR)
				fatal_error("error in add_substitution() in split_subsitutions()");
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

char						*command_substition(char const *word)
{
	t_strlist	*strlist;
	char		*result;

	strlist = split_subsitutions(word);
	result = strlist_to_str(strlist);
	strlist_delete(&strlist);
	return (result);
}
