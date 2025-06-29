/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:58:10 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:42:05 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*out;

	size = ft_strlen(s1);
	size += ft_strlen(s2);
	out = malloc(size + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
		out[i++] = s2[j++];
	out[i] = 0;
	return (out);
}
