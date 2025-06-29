/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:20:03 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/14 14:43:11 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"
#include <stdarg.h>

void	put_arg_format(va_list *args, t_format *fmt, char **line, int *len)
{
	char			*formatted;
	unsigned char	c;

	if (fmt->type == e_str)
		formatted = put_str_format(va_arg(*args, void *), *fmt);
	else if (fmt->type == e_int)
		formatted = put_int_format(va_arg(*args, int), *fmt);
	else if (fmt->type == e_hex)
		formatted = put_hex_format(va_arg(*args, int), *fmt);
	else if (fmt->type == e_ptr)
		formatted = put_ptr_format(va_arg(*args, void *), *fmt);
	else if (fmt->type == e_unsigned)
		formatted = put_unsigned_format(va_arg(*args, unsigned int), *fmt);
	else if (fmt->type == e_char)
	{
		c = va_arg(*args, int);
		if (c == 0)
			(*len)++;
		formatted = put_char_format(c, *fmt);
	}
	else if (fmt->type == e_pcnt)
		formatted = ft_strdup("%");
	else
		formatted = NULL;
	*line = ft_join_or_start(*line, formatted);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	char			*output;
	int				len;
	t_format		fmt;

	len = 0;
	output = NULL;
	va_start(args, format);
	while (*format)
	{
		if (!extract_til_conv(&format, &output))
			break ;
		if (!extract_format(&format, &fmt))
			return (-1);
		put_arg_format(&args, &fmt, &output, &len);
	}
	ft_putstr_fd(output, 1);
	len += ft_strlen(output);
	free(output);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list			args;
	char			*output;
	int				len;
	t_format		fmt;

	len = 0;
	output = NULL;
	va_start(args, format);
	while (*format)
	{
		if (!extract_til_conv(&format, &output))
			break ;
		if (!extract_format(&format, &fmt))
			return (-1);
		put_arg_format(&args, &fmt, &output, &len);
	}
	ft_putstr_fd(output, fd);
	len += ft_strlen(output);
	free(output);
	return (len);
}
