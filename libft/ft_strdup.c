/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:24:02 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:27:02 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*out;
	int		i;

	i = 0;
	while (s[i] != 0)
		i++;
	out = malloc(i + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
