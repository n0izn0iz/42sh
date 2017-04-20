#include "history.h"
#include "abstract_list.h"
#include "utils.h"
#include "file_positions.h"

void		add_to_history_list(t_history **list, t_history *new)
{
	t_history *tmp;

	if (new)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

t_history	*create_history_entry(char *line)
{
	t_history *new;

	if (line && ft_strcmp(line, "\n"))
	{
		new = (t_history *)memalloc_or_die(sizeof(t_history));
		new->line = ft_strdup(line);
		new->appended = false;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}

void		history_add_with_nl(t_shell_env *shell_env, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	add_to_history_list(&shell_env->history.list, create_history_entry(tmp));
	ft_strdel(&tmp);
}

void		load_history(t_shell_env *shell_env, char *filename, bool n_opt)
{
	char	*line;
	int		fd;
	int		i;
	int		position;

	i = 0;
	position = 0;
	if (!filename)
		filename = HISTFILE;
	if ((fd = open(filename, O_RDWR | O_CREAT, 0644)) < 0)
		;//set_file_error
	else
	{
		if (n_opt)
			position = get_file_position(filename)->position;
		while ((line = ft_getline(fd)))
		{
			if (i >= position)
				history_add_with_nl(shell_env, line);
			ft_strdel(&line);
			i++;
		}
		close(fd);
		update_file_position(filename, i);
	}
}
