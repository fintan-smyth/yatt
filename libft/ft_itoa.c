/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:03 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 15:47:18 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*out;
	long	num;
	int		i;

	i = count_digits(n);
	out = malloc(i + 1);
	if (out == NULL)
		return (NULL);
	num = (long)n;
	if (num < 0)
	{
		out[0] = '-';
		num *= -1;
	}
	out[i--] = 0;
	out[i--] = (num % 10) + '0';
	num /= 10;
	while (num != 0)
	{
		out[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (out);
}
/*
int main(void)
{
	int	n1 = 471964219;
	int n2 = -1;
	int	n3 = -37146;
	int	n4 = 2147483647;
	int	n5 = -2147483648;

	printf("%s\n", ft_itoa(n1));
	printf("%s\n", ft_itoa(n2));
	printf("%s\n", ft_itoa(n3));
	printf("%s\n", ft_itoa(n4));
	printf("%s\n", ft_itoa(n5));
}
*/
