/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:44:19 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/27 12:44:40 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"

size_t	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_output_len(char *str)
{
	int	len;
	int	in_escape;

	len = 0;
	in_escape = 0;
	while (*str)
	{
		if (*str == '\e')
			in_escape = 1;
		else if (in_escape == 1)
		{
			if (ft_isalpha(*str))
				in_escape = 0;
		}
		else
			len++;
		str++;
	}
	return (len);
}

int	print_str_centred(char *str, int row, int width)
{
	int	start_x;
	int	len;

	len = ft_output_len(str);
	start_x = (width - len) / 2 + 1;
	ft_printf("\e[%d;%dH%s", row, start_x, str);
	return (start_x);
}
