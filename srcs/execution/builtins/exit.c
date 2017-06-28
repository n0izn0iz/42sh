/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:53:03 by asenat            #+#    #+#             */
/*   Updated: 2017/06/28 15:22:37 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "history/builtin/history.h"
#include "utils.h"
#include <libft.h>

int		builtin_exit(int argc, char **argv)
{
	int			ret;

	if (argc > 1)
		ret = ft_atoi(argv[1]);
	else
		ret = get_last_exit_status();
	if (ret < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: wrong exit value: %d\n", SHNAME, ret);
		ret = 2;
	}
	else if (ret > 255)
	{
		ret = ret % 256;
	}
	exit(ret);
}
