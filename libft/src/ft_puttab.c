/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:10:41 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/14 15:38:41 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab(char **tab)
{
	size_t i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			ft_putstr(tab[i++]);
			ft_putchar('\n');
		}
	}
}