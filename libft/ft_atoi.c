/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:47:32 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:26:38 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;

	sign = 1;
	while ((*str == ' ') || (*str <= '\r' && *str >= '\t'))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	i = 0;
	while (*str <= '9' && *str >= '0')
	{
		i *= 10;
		i += (*str - '0');
		str++;
	}
	return (i * sign);
}
/*
int main(void)
{
	char *s1 = "    \n +124";

	printf("%d\n", atoi(s1));
	printf("%d\n", ft_atoi(s1));
}
*/
