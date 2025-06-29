/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:40:11 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:08 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

char	get_hex_digit(int n, int upper)
{
	if (n < 10)
		return (n + '0');
	else if (upper)
		return ((n - 10) + 'A');
	else
		return ((n - 10) + 'a');
}

void	ft_puthex_buf(char *buf, int n, t_format fmt)
{
	int				i;
	int				upper;
	unsigned int	num;

	upper = 0;
	if (fmt.hex_char == 'X')
		upper = 1;
	num = (unsigned int)n;
	i = 0;
	buf[i++] = get_hex_digit((num % 16), upper);
	num /= 16;
	while (num != 0)
	{
		buf[i++] = get_hex_digit((num % 16), upper);
		num /= 16;
	}
	buf[i] = 0;
	ft_strrev(buf);
}

void	format_hex(char *buf, t_format fmt)
{
	char	*precp;
	char	*widthp;
	char	padchar;

	padchar = ' ';
	precp = buf;
	widthp = buf;
	pad_str_left(precp, fmt.precision, '0');
	if (fmt.alt && ft_strncmp(buf, "0", 2) != 0)
	{
		pad_str_left(widthp, ft_strlen(buf) + 1, fmt.hex_char);
		pad_str_left(widthp, ft_strlen(buf) + 1, '0');
		precp += 2;
	}
	if (fmt.l_adj)
		pad_str_right(buf, fmt.field_width, ' ');
	if (fmt.zero_pad && fmt.precision < 0)
	{
		padchar = '0';
		widthp = precp;
		if (fmt.alt)
			fmt.field_width -= 2;
	}
	if (!fmt.l_adj)
		pad_str_left(widthp, fmt.field_width, padchar);
}

char	*put_hex_format(int num, t_format fmt)
{
	char	*buf;
	int		allocsize;

	if (fmt.field_width > 10 || fmt.precision > 10)
		allocsize = ft_max(fmt.field_width, fmt.precision) + 1;
	else
		allocsize = 11;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	ft_puthex_buf(buf, num, fmt);
	format_hex(buf, fmt);
	return (buf);
}
