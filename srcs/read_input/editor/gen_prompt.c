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

// #include "history/history.h"

#include "variable.h"

typedef struct		s_unmatched_def
{
	t_error_id	id;
	char const	*str;
}					t_unmatched_def;

static char const	*get_unmatched_str(t_error_id id)
{
	static t_unmatched_def	const	defs[] = {
		{ UNMATCHED_SINGLE_QUOTE, "quote" },
		{ UNMATCHED_DOUBLE_QUOTE, "dquote" },
		{ UNMATCHED_BACKQUOTE, "bquote" },
		{ UNEXPECTED_IF, "cmdif" },
		{ UNEXPECTED_PIPE, "pipe" },
	};
	size_t							u;

	u = 0;
	while (u < 6)
	{
		if (defs[u].id == id)
			return (defs[u].str);
		u++;
	}
	return ("unknown");
}

static char			*get_hostname()
{
	char 	*result;
	int		fd;
	int		ret;

	result = memalloc_or_die(sizeof(char) * 4096);
	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	ret = read(fd, result, 4095);
	if (ret <= 0)
		return (ft_strdup(""));
	result[ret - 1] = '\0';
	return (result);
}

static char			*mangle_home(char *str)
{
	char	*result;
	char	*home_str;
	size_t	home_str_len;

	home_str = get_variable("HOME");
	result = ft_strstr(str, home_str);
	home_str_len = ft_strlen(home_str);
	free(home_str);
	if (result == NULL)
		return (str);
	result = ft_strjoin("~", result + home_str_len);
	free(str);
		return(result);
}

char				*gen_prompt(void)
{
	char		*result;
	char		*tmp;
	t_shell_env	*shell_env;

	shell_env = get_shell_env();
	if (!shell_env->last_unmatched)
	{
		tmp = ft_strjoinf(mangle_home(get_variable("PWD")), "]$ ", 1);
		result = ft_strjoin(" ", tmp);
		free(tmp);
		tmp = ft_strjoinf(get_variable("USER"), "@", 1);
		tmp = ft_strjoinf(tmp, get_hostname(), 3);
		tmp = ft_strjoinf("[", tmp, 2);
		result = ft_strjoinf(tmp, result, 3);
	}
	else
	 	result = ft_strjoin(get_unmatched_str(shell_env->last_unmatched), "> ");

	return (result);
}
