/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:03:40 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/08 20:06:41 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

int	handle_flags(char c, t_format *fmt)
{
	if (c == ' ' || c == '+')
	{
		if (fmt->pos_pad == 1)
			return (0);
		set_pos_fmt(c, fmt);
	}
	else if (c == '-')
	{
		if (fmt->l_adj == 1)
			return (0);
		fmt->l_adj = 1;
	}
	else if (c == '#')
	{
		if (fmt->alt == 1)
			return (0);
		fmt->alt = 1;
	}
	else if (c == '0')
	{
		if (fmt->zero_pad == 1)
			return (0);
		fmt->zero_pad = 1;
	}
	return (1);
}

void	handle_conv_char(char c, t_format *fmt)
{
	if (c == 'i' || c == 'd')
		fmt->type = e_int;
	else if (c == 'x')
	{
		fmt->type = e_hex;
		fmt->hex_char = 'x';
	}
	else if (c == 'X')
	{
		fmt->type = e_hex;
		fmt->hex_char = 'X';
	}
	else if (c == 'p')
		fmt->type = e_ptr;
	else if (c == 'u')
		fmt->type = e_unsigned;
	else if (c == 's')
		fmt->type = e_str;
	else if (c == 'c')
		fmt->type = e_char;
	else if (c == '%')
		fmt->type = e_pcnt;
}

int	parse_format_string(char *str, t_format *fmt, char *conv_chars)
{
	while (ft_strchr("0- +#", *str) != NULL)
	{
		if (handle_flags(*str, fmt) == 0)
			return (0);
		str++;
	}
	if (ft_atoi(str) != 0)
		fmt->field_width = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '.')
	{
		str++;
		fmt->precision = ft_atoi(str);
		if (*str == '-')
			str++;
		while (*str >= '0' && *str <= '9')
			str++;
	}
	if (ft_strchr(conv_chars, *str) == NULL || !(*str))
		return (0);
	handle_conv_char(*str, fmt);
	return (1);
}

int	extract_format(const char **str, t_format *fmt)
{
	int		len;
	char	*format;

	len = 0;
	while (ft_strchr("diuxXspc%", (*str)[len]) == NULL)
		len++;
	if ((*str)[len] == 0)
		return (0);
	format = ft_strndup(*str, len + 1);
	clear_t_format(fmt);
	if (!parse_format_string(format, fmt, "diuxXspc%"))
		return (0);
	free(format);
	(*str) += len + 1;
	return (1);
}
