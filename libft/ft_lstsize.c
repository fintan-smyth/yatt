/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:27:17 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 12:11:03 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*current;

	if (lst == NULL)
		return (0);
	current = lst;
	len = 0;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}
