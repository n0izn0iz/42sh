#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdlib.h>
# include <libft.h>
# include "bool.h"

typedef struct			s_history
{
	struct s_history	*next;
	char				*line;
	struct s_history	*prec;
}						t_history;

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	t_bool				exported;
}						t_variable;

typedef struct			s_shell_env
{
	t_variable			*variables;
	t_history			*history;
}						t_shell_env;

t_shell_env				*get_shell_env(void);

/*struct s_abstract_list
{
	struct s_abstract_list	*next;
}

struct s_abstract_list
{
	struct s_abstract_list	*next;
	struct s_abstract_list	*prev;
}


size_t count_list(s_abstract_list *it);*/

#endif