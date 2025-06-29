/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:39:08 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:36 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

void	set_pos_fmt(char poschar, t_format *fmt)
{
	fmt->pos_pad = 1;
	fmt->pos_char = poschar;
}

void	clear_t_format(t_format *fmt)
{
	fmt->field_width = 0;
	fmt->precision = -1;
	fmt->l_adj = 0;
	fmt->zero_pad = 0;
	fmt->alt = 0;
	fmt->pos_pad = 0;
	fmt->pos_char = 0;
	fmt->hex_char = 'x';
	fmt->type = -1;
}

int	extract_til_conv(const char **format, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*format)[len] != '%' && (*format)[len] != 0)
		len++;
	temp = ft_strndup(*format, len);
	*line = ft_join_or_start(*line, temp);
	if ((*format)[len] == 0)
		return (0);
	(*format) += len + 1;
	return (1);
}

void	pad_str_right(char *buf, int width, char c)
{
	int	len;

	len = ft_strlen(buf);
	while (len < width)
	{
		buf[len] = c;
		len++;
	}
	buf[len] = 0;
}

void	pad_str_left(char *buf, int width, char c)
{
	int	len;

	len = ft_strlen(buf);
	if (len < width)
	{
		ft_memmove(&buf[width - len], buf, len + 1);
		ft_memset(buf, c, width - len);
	}
}
// void	print_t_format(t_format fmt)
// {
// 	ft_printf("field_width:\t%d\n", fmt.field_width);
// 	ft_printf("precision:\t%d\n", fmt.precision);
// 	ft_printf("l_adj:\t\t%d\n", fmt.l_adj);
// 	ft_printf("zero_pad:\t%d\n", fmt.zero_pad);
// 	ft_printf("alt:\t\t%d\n", fmt.alt);
// 	ft_printf("pos_pad:\t%d\n", fmt.pos_pad);
// 	ft_printf("pos_char:\t%c\n", fmt.pos_char);
// 	ft_printf("hex_char:\t%c\n", fmt.hex_char);
// 	ft_printf("type:\t\t%d\n", fmt.type);
// }
