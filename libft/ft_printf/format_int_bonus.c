/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:45:22 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:16 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

void	ft_putint_buf(char *buf, int n, t_format fmt)
{
	int		i;
	long	num;
	int		sign;

	num = (long)n;
	sign = 1;
	i = 0;
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	buf[i++] = (num % 10) + '0';
	num /= 10;
	while (num != 0)
	{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (sign < 0)
		buf[i++] = '-';
	buf[i] = 0;
	ft_strrev(buf);
	if (fmt.precision == 0 && n == 0)
		buf[i - 1] = 0;
}

void	format_int(char *buf, int num, t_format fmt)
{
	char	*precp;
	char	*widthp;
	char	padchar;

	padchar = ' ';
	precp = buf;
	widthp = buf;
	if (num < 0 || (fmt.pos_pad && num >= 0))
		precp++;
	if (fmt.pos_pad && num >= 0)
		pad_str_left(buf, ft_strlen(buf) + 1, fmt.pos_char);
	pad_str_left(precp, fmt.precision, '0');
	if (fmt.l_adj)
	{
		pad_str_right(buf, fmt.field_width, ' ');
		return ;
	}
	if (fmt.zero_pad && fmt.precision < 0)
	{
		padchar = '0';
		widthp = precp;
		if (num < 0 || (fmt.pos_pad && num >= 0))
			fmt.field_width--;
	}
	pad_str_left(widthp, fmt.field_width, padchar);
}

char	*put_int_format(int num, t_format fmt)
{
	char	*buf;
	int		allocsize;

	if (fmt.field_width > 12 || fmt.precision > 12)
		allocsize = ft_max(fmt.field_width, fmt.precision) + 2;
	else
		allocsize = 14;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	ft_putint_buf(buf, num, fmt);
	format_int(buf, num, fmt);
	return (buf);
}
