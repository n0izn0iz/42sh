#include "syntax_tree.h"
#include "utils.h"
#include <libft.h>

static void print_simple_command(t_simple_command const *cmd, size_t lvl)
{
	char **it;
	print_n_char(' ', (lvl) * 2);
	ft_putstr("command: ");
	it = cmd->argv;
	while ((*it) != NULL)
	{
		if (it != cmd->argv)
			ft_putchar(' ');
		ft_putendl(*it);
		it++;
	}
	ft_putchar('\n');
}

static void print_pipeline(t_simple_command const *pip, size_t lvl)
{
	if (pip == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (pip->next == NULL)
	{
		print_simple_command(pip, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("pipeline:");
	while (pip != NULL)
	{
		print_simple_command(pip, lvl + 1);
		pip = pip->next;
		if (pip != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar('|');
			ft_putchar('\n');
		}
	}
}

static void print_ao_sep(t_ao_type sep_type, size_t lvl)
{
	if (sep_type == AO_END)
		return ;
	print_n_char(' ', lvl * 2);
	if (sep_type == AO_AND)
		ft_putstr("&&");
	else if (sep_type == AO_OR)
		ft_putstr("||");
	else
		ft_putstr("BUG");
	ft_putchar('\n');
}

static void	print_and_or_list(t_and_or_list const *ao_list, size_t lvl)
{
	if (ao_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (ao_list->next == NULL)
	{
		print_pipeline(ao_list->pipeline, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("and_or_list:");
	while (ao_list != NULL)
	{
		print_pipeline(ao_list->pipeline, lvl + 1);
		if (ao_list->next != NULL)
			print_ao_sep(ao_list->separation_type, lvl);
		ao_list = ao_list->next;
	}
}

void	print_command_list(t_command_list const *cmd_list, size_t lvl)
{
	if (cmd_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (cmd_list->next == NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("command_list:");
	while (cmd_list != NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl + 1);
		cmd_list = cmd_list->next;
		if (cmd_list != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar(';');
			ft_putchar('\n');
		}
	}
}
