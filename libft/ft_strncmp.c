/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:17 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:26:01 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (*s1 != *s2)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	if (*s1++ == '\0')
		return (0);
	s2++;
	while (--n > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*s1++ == '\0')
			break ;
		s2++;
	}
	return (0);
}
