/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:23:40 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:26:51 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (*to_find == 0)
		return ((char *)str);
	j = 0;
	while (str[j])
	{
		i = 0;
		while ((to_find[i] == str[j + i]) && str[i + j] != 0 && (j + i) < len)
			i++;
		if (to_find[i] == 0)
			return ((char *)(str + j));
		j++;
	}
	return (NULL);
}
/*
int main(void)
{
	char	*s1 = "this is a test string";
	char	*s2 = "test";

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	printf("ft_strnstr(s1, s2, 21): %s\n", ft_strnstr(s1, s2, 21));
	printf("ft_strnstr(s1, s2, 14): %s\n", ft_strnstr(s1, s2, 14));
	printf("ft_strnstr(s1, s2, 13): %s\n", ft_strnstr(s1, s2, 13));
}
*/
