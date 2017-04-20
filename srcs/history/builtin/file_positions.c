#include "shell_env.h"
#include "file_positions.h"
#include "abstract_list.h"
#include <libft.h>

void			print_file_positions(void)
{
	t_file_position *files;

	files = get_shell_env()->history_files;
	ft_putendl("<history file positions>");
	while (files)
	{
		ft_printf("File name: %s\nPosition: %d\n", files->filename, \
					files->position);
		files = files->next;
	}
	ft_putendl("</history file positions>");
}

t_file_position	*get_file_position(char *filename)
{
	t_file_position *files;

	files = get_shell_env()->history_files;
	while (files)
	{
		if (!ft_strcmp(files->filename, filename))
			return (files);
		files = files->next;
	}
	return (NULL);
}

void			free_file_positions(t_file_position **files_addr)
{
	if (*files_addr)
	{
		free_file_positions(&(*files_addr)->next);
		ft_strdel(&(*files_addr)->filename);
		free(*files_addr);
		*files_addr = NULL;
	}
}

static void		new_file_position(char *filename, int position)
{
	t_file_position *files;
	t_file_position *new;

	files = get_shell_env()->history_files;
	new = memalloc_or_die(sizeof(t_file_position));
	new->filename = ft_strdup(filename);
	new->position = position;
	new->next = NULL;
	list_push_back((t_abstract_list **)&get_shell_env()->history_files, \
					(t_abstract_list *)new);
}

void			update_file_position(char *filename, int new_position)
{
	t_file_position *files;

	if (!(files = get_file_position(filename)))
		new_file_position(filename, new_position);
	else
		files->position = new_position;
}
