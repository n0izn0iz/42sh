#ifndef STRLIST_H
# define STRLIST_H

#include <stdbool.h>

typedef struct		s_strlist
{
	struct s_strlist	*next;
	char				*str;
	bool				to_split;
}					t_strlist;

t_strlist			*strlist_construct(char const *str);
char				**strlist_to_strarray(t_strlist const *list);
void				strlist_delete(t_strlist **strlist_addr);
void				strlist_append(t_strlist **strlist_addr , char const *str);
#endif
