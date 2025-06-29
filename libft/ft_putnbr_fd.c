/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:31:43 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 16:34:47 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	long	num;
	char	s[12];
	int		sign;

	num = (long)n;
	sign = 1;
	i = 0;
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	s[i++] = (num % 10) + '0';
	num /= 10;
	while (num != 0)
	{
		s[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (sign < 0)
		s[i++] = '-';
	while (i > 0)
		write(fd, &s[--i], 1);
}
/*
int	main(void)
{
	ft_putnbr_fd(2147483647, 1);
	printf("\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
	ft_putnbr_fd(0, 1);
	printf("\n");
}
*/
