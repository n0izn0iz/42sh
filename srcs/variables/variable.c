#include "shell_env.h"
#include "utils.h"
#include "abstract_list.h"

t_variable	*create_variable(char const *name, char const *value,
	bool exported)
{
	t_variable *v;

	v = memalloc_or_die(sizeof(t_variable));
	v->name = ft_strdup(name);
	v->value = ft_strdup(value);
	v->exported = exported;
	v->overwrite = true;
	v->is_variable = true;
	v->is_function = false;
	v->next = NULL;
	return (v);
}

bool		is_a_variable(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->is_variable)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

bool		is_a_function(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->is_function)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

void		print_variable(t_variable *v)
{
	while (v)
	{
		ft_printf("Name: \"%s\"	", v->name);
		ft_printf("Value: \"%s\"	", v->value);
		if (v->is_variable)
			ft_printf("VARIABLE	");
		if (v->is_function)
			ft_printf("FUNCTION	");
		if (v->exported)
			ft_printf("FOR EXPORT	");
		if (v->overwrite)
			ft_printf("OVERWRITE	");
		ft_printf("\n");
		v = v->next;
	}
}

bool		variable_exist(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			return (true);
		}
		v = v->next;
	}
	return (false);
}

bool		variable_is_overwritable(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->overwrite)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

bool		set_variable_for_export(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			v->exported = true;
			return (true);
		}
		v = v->next;
	}
	return (false);
}

void		free_variable(t_variable *list)
{
	if (list)
	{
		free(list->name);
		free(list->value);
		free(list);
	}
}

void		delete_variable(t_variable **var)
{
	free_variable(*var);
	*var = NULL;
}

void		delete_all_variables(t_variable **var)
{
	t_variable	*it;
	t_variable	*tmp;

	it = *var;
	while (it)
	{
		tmp = it->next;
		free_variable(it);
		it = tmp;
	}
	*var = NULL;
}

int		pop_variable_by_name(t_variable **list, char *name)
{
	t_variable *lst;
	t_variable **addr;

	lst = *list;
	addr = list;
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
		{
			*addr = lst->next;
			free_variable(lst);
			return (STATUS_SUCCESS);
		}
		addr = &(*addr)->next;
		lst = *addr;
	}
	return (STATUS_FAILURE);
}

t_variable *copy_variable(t_variable *e)
{
	t_variable	*tmp;
	t_variable	*new;

	tmp = NULL;
	while (e)
	{
		new = create_variable(e->name, e->value, e->exported);
		list_push_back((t_abstract_list**)&tmp, (t_abstract_list*)new);
		e = e->next;
	}
	return (tmp);
}
