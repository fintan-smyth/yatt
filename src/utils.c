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
