/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:34 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 13:04:22 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	test_func(unsigned int n, char c)
{
	char	result;

	result = c + n;
	return (result);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	int		i;

	out = malloc(ft_strlen(s) + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		out[i] = f(i, s[i]);
		i++;
	}
	out[i] = 0;
	return (out);
}
/*
int main(void)
{
	char	*s1 = "00000000000000000000"; 

	printf("%s\n", ft_strmapi(s1, test_func));
}
*/
