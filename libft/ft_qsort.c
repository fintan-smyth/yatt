/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:08:55 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/02 14:38:04 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_arr_pos(void **array, int i, int j)
{
	void	*temp;

	if (i == j)
		return ;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void	ft_qsort(void **array, int left, int right,
			int (*cmp)(void *, void *))
{
	int	i;
	int	last;

	if (left >= right)
		return ;
	swap_arr_pos(array, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (cmp(array[left], array[i]) > 0)
			swap_arr_pos(array, ++last, i);
		i++;
	}
	swap_arr_pos(array, left, last);
	ft_qsort(array, left, last - 1, cmp);
	ft_qsort(array, last + 1, right, cmp);
}
