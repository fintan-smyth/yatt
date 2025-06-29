/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:27:15 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 16:54:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	s_len;
	size_t			i;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	if ((unsigned int)len < (s_len - start))
		sub = malloc(len + 1);
	else
		sub = malloc((s_len - start) + 1);
	i = 0;
	if (sub == NULL)
		return (NULL);
	while (s[start] != 0 && i < len)
		sub[i++] = s[start++];
	sub[i] = 0;
	return (sub);
}
