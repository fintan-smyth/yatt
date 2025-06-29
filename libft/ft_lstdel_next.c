/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:45:40 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/30 23:48:28 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_next(t_list *lst, void (*del)(void *))
{
	t_list	*next;

	if (lst == NULL)
		return ;
	if (lst->next == NULL)
		return ;
	next = lst->next->next;
	ft_lstdelone(lst->next, del);
	lst->next = next;
}
