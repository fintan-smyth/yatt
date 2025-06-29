/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_exists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:32:37 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/14 18:32:48 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_exists(t_list *lst, void *match, int (*cmp)(void *, void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (cmp(current->content, match) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
