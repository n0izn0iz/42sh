#include "history.h"
#include "history/substitution/history_substitutions.h"
#include "abstract_list.h"
#include "utils.h"

/*
**	option -p prints the result of the substituted arguments
**	option -s saves the result of the substituted arguments to the history list
*/

static void		args_manipulation(t_history **history, t_hist_opt options)
{
	char	*args;
	int		i;

	i = 0;
	if (options.s)
	{
		delete_entry_at(history, list_count((t_abstract_list *)*history));
		if ((args = array_to_str(options.args)))
		{
			history_add_with_nl(get_shell_env(), args);
			ft_strdel(&args);
		}
	}
	else if (options.args)
	{
		while (options.args[i])
		{
			/*
			   quotes should already have been removed
			   + normal substitution made
			   (test with quotes etc when execution loop)
			   */
			history_substitution(&options.args[i]);
			i++;
		}
		ft_puttab(options.args);
		delete_entry_at(history, list_count((t_abstract_list *)*history));
	}
}

/*
**		-w (write) and -a (append) write the history list to a a file
**		-r (read all) and -n (continue reading) read history from a file
*/

static void		file_manipulation(t_hist_opt options, t_history *history)
{
	char		*filename;

	if (options.args)
		filename = options.args[0];
	else
		filename = HISTFILE;
	if (options.anrw & W_OPT || options.anrw & A_OPT)
	{
		if (options.anrw & W_OPT)
			hist_to_file(history, filename, false);
		else
			hist_to_file(history, filename, true);
	}
	else if (options.anrw & R_OPT || options.anrw & N_OPT)
	{
		if (options.anrw & R_OPT)
			load_history(get_shell_env(), filename, 0);
		else
			load_history(get_shell_env(), filename, 1);
	}
}

void			execute_options(t_history **history, t_hist_opt options)
{
	if (options.s || options.p)
		args_manipulation(history, options);
	else if (options.d || options.c)
	{
		if (options.c)
			clear_history_list(history);
		else
		{
			if (!options.offset)
				options.offset = ft_strdup(options.args[0]);
			delete_history_entry(history, options.offset);
		}
	}
	else if (options.anrw)
		file_manipulation(options, *history);
	else if (options.args)
	{
		ft_puttab(options.args);
		if (options.ac > 1)
			error_builtin("history", NULL, TOO_MANY_ARGS);
		else if (str_is_digits(*options.args))
			print_history(*history, list_count((t_abstract_list *)history) - ft_atoi(*options.args));
			//print_history_n(i + 1 < options.ac, options.args[0], history);
		else
			error_builtin("history", NULL, NEED_NUM);
	}
	else
		print_history(*history, 0);
}
