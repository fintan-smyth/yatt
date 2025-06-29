/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:38 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 12:05:25 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*chars1;
	unsigned char	*chars2;
	size_t			i;

	chars1 = (unsigned char *)s1;
	chars2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (chars1[i] != chars2[i])
			return (chars1[i] - chars2[i]);
		i++;
	}
	return (0);
}
