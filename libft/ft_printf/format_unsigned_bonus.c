/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:15:51 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/07 21:35:33 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
#include "ft_printf_bonus.h"

void	ft_putunsigned_buf(char *buf, unsigned int n, t_format fmt)
{
	int				i;
	unsigned int	num;

	num = n;
	i = 0;
	buf[i++] = (num % 10) + '0';
	num /= 10;
	while (num != 0)
	{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	buf[i] = 0;
	ft_strrev(buf);
	if (fmt.precision == 0 && n == 0)
		buf[i - 1] = 0;
}

void	format_unsigned(char *buf, t_format fmt)
{
	char	padchar;

	padchar = ' ';
	pad_str_left(buf, fmt.precision, '0');
	if (fmt.l_adj)
	{
		pad_str_right(buf, fmt.field_width, ' ');
		return ;
	}
	if (fmt.zero_pad && fmt.precision < 0)
		padchar = '0';
	pad_str_left(buf, fmt.field_width, padchar);
}

char	*put_unsigned_format(unsigned int num, t_format fmt)
{
	char	*buf;
	int		allocsize;

	if (fmt.field_width > 12 || fmt.precision > 12)
		allocsize = ft_max(fmt.precision, fmt.field_width) + 1;
	else
		allocsize = 13;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	ft_putunsigned_buf(buf, num, fmt);
	format_unsigned(buf, fmt);
	return (buf);
}
