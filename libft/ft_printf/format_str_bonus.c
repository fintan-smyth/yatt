/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:48:43 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

void	format_string(char *buf, t_format fmt)
{
	if (fmt.precision >= 0)
		buf[fmt.precision] = 0;
	if (fmt.l_adj)
		pad_str_right(buf, fmt.field_width, ' ');
	else
		pad_str_left(buf, fmt.field_width, ' ');
}

char	*put_str_format(char *s, t_format fmt)
{
	char	*buf;
	int		len;
	int		allocsize;
	int		alloced;

	alloced = 0;
	if (s == NULL)
	{
		alloced = 1;
		s = ft_strdup("(null)");
	}
	len = ft_strlen(s);
	if (len > fmt.field_width && len > fmt.precision)
		allocsize = len + 5;
	else
		allocsize = ft_max(fmt.field_width, fmt.precision) + 5;
	buf = malloc(allocsize);
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, s, allocsize);
	if (alloced)
		free(s);
	format_string(buf, fmt);
	return (buf);
}
