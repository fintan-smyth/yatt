/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:24:02 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/29 15:43:17 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	i = 0;
	while (s[i] != 0 && i < n)
		i++;
	out = malloc(i + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0 && i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
