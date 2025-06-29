/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:50:38 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/07 21:05:30 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
#include "ft_printf_bonus.h"

char	*put_char_format(unsigned char c, t_format fmt)
{
	char	*buf;
	int		allocsize;

	if (fmt.field_width > 1 || fmt.precision > 1)
		allocsize = ft_max(fmt.field_width, fmt.precision) + 1;
	else
		allocsize = 2;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	buf[0] = c;
	buf[1] = 0;
	if (c == 0)
		fmt.field_width--;
	if (fmt.l_adj)
		pad_str_right(buf, fmt.field_width, ' ');
	else
		pad_str_left(buf, fmt.field_width, ' ');
	return (buf);
}
