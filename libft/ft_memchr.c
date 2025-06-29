/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:48:29 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 13:02:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chars;
	size_t			i;

	chars = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (chars[i] == (unsigned char)c)
			return ((void *)(chars + i));
		i++;
	}
	return (NULL);
}
