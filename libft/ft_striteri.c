/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:06:20 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 16:16:30 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	test_func(unsigned int n, char *c)
{
	*c = *c + n;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int main(void)
{
	char	*s1 = "00000000";
	char	s2[100];

	ft_strlcpy(s2, s1, 100);
	ft_striteri(s2, test_func);
	printf("%s\n", s2);
}
*/
