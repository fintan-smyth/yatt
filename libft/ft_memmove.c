/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:50:02 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/30 14:54:12 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*cdest;
	char	*csrc;
	size_t	i;

	cdest = (char *) dest;
	csrc = (char *) src;
	if (dest == src)
		return (dest);
	if ((size_t)(dest - src) < n && dest - src > 0)
	{
		while (n-- > 0)
			cdest[n] = csrc[n];
		return (dest);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
		return (dest);
	}
}
/*
int	main(void)
{
	char	s1[100];
	char	*s2 = s1 + 5;
	strcpy(s1, "this is a test string");

	memmove(s2, s1, 22);
	printf("%s\n", s2);
}
*/
