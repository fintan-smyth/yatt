/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwhitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:57:54 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/30 14:00:45 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strwhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
