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

void	add_passive_string(t_strlist **strlist_addr, char const *start,
			char const *end)
{
	char	*tmp;

	tmp = strdup_until(start, end);
	strlist_append(strlist_addr, tmp);
	free(tmp);
}

char	*fd_to_str(int fd)
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

void	rm_trailing_newlines(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len-- > 0 && str[len] == '\n')
		str[len] = '\0';
}

char			*command_substition(char const *word)
{
	t_strlist	*strlist;
	char		*result;

	strlist = split_subsitutions(word);
	result = strlist_to_str(strlist);
	strlist_delete(&strlist);
	return (result);
}
