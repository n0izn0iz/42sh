#include <libft.h>
#include "history_options.h"
#include "errors.h"

void			free_history_options(t_hist_opt *options)
{
	if (options->offset)
		ft_strdel(&(options->offset));
	if (options->args && options->args[0])
		ft_freetabchar(options->args);
}

static int 	get_anrw_options(char c, t_hist_opt *options)
{
	if (options->anrw)
		return (-1);
	if (c == 'a')
		options->anrw = A_OPT;
	else if (c == 'w')
		options->anrw = W_OPT;
	else if (c == 'r')
		options->anrw = R_OPT;
	else if (c == 'n')
		options->anrw = N_OPT;
	return (0);
}

static bool	check_cd_opt(char **arg, t_hist_opt *options)
{
	if (**arg == 'c')
	{
		options->c = 1;
		return (1);
	}
	else if (**arg == 'd')
	{
		options->d = 1;
		if (*(*arg + 1))
			options->offset = ft_strdup(++(*arg));
		return (1);
	}
	return (0);
}

bool		get_hist_options(char *arg, t_hist_opt *options)
{
	bool	ret;

	options->ac++;
	arg++;
	ret = 1;
	while (arg && *arg)
	{
		if (check_cd_opt(&arg, options))
			;
		else if (ft_strchr("anrw", *arg))
		{
			if (get_anrw_options(*arg, options) < 0)
			{
				error_builtin("history", NULL, ANRW);
				return (0);
			}
		}
		else if (*arg == 'p')
			options->p = 1;
		else if (*arg == 's')
			options->s = 1;
		else if (*arg == '-' && ret ==1)
			ret = 0;
		else
		{
			error_builtin("history", ft_strdup(arg), INVALID_OPTION);
			return (0);
		}
		arg++;
	}
	return (ret);
}