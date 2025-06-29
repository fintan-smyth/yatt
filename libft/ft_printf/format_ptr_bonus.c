/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_ptr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:43:03 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:16 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

void	ft_putptr_buf(char *buf, void *ptr)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = (unsigned long)ptr;
	buf[i++] = get_hex_digit((num % 16), 0);
	num /= 16;
	while (num != 0)
	{
		buf[i++] = get_hex_digit((num % 16), 0);
		num /= 16;
	}
	buf[i] = 0;
	ft_strrev(buf);
}

void	format_ptr(char *buf, t_format fmt)
{
	char	padchar;

	padchar = ' ';
	if (ft_strncmp("(nil)", buf, 6) != 0)
	{
		pad_str_left(buf, ft_strlen(buf) + 1, fmt.hex_char);
		pad_str_left(buf, ft_strlen(buf) + 1, '0');
	}
	if (fmt.l_adj)
		pad_str_right(buf, fmt.field_width, ' ');
	if (!fmt.l_adj)
		pad_str_left(buf, fmt.field_width, padchar);
}

char	*put_ptr_format(void *ptr, t_format fmt)
{
	char	*buf;
	int		allocsize;

	if (fmt.field_width > 16 || fmt.precision > 16)
		allocsize = ft_max(fmt.field_width, fmt.precision) + 5;
	else
		allocsize = 21;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	if (ptr != NULL)
		ft_putptr_buf(buf, ptr);
	else
		ft_strlcpy(buf, "(nil)", allocsize);
	format_ptr(buf, fmt);
	return (buf);
}
