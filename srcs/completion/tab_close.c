/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:13:41 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:14:01 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void		insert_to_str(t_editor *ed, char *to_write)
{
	while (*to_write)
	{
		add_to_string(ed, *to_write);
		++to_write;
	}
}

void			tab_close(t_editor *ed, char *line)
{
	t_strlist	*tmp;
	char		*to_write;
	int			i;

	tmp = get_tabinfo()->list;
	i = get_tabinfo()->selected_index;
	while (i--)
		tmp = tmp->next;
	i = ft_strlen(get_tabinfo()->file_prefix);
	to_write = tmp->str + i;
	insert_to_str(ed, to_write);
	clear_tabinfo();
	(void)line;
}

void			tab_cancel(t_editor *ed, char *line)
{
	(void)line;
	clear_down(ed);
	clear_tabinfo();
}
