/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:11:26 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/30 13:55:06 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return ;
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*lst = ft_lstnew(NULL);
	t_list	*new = ft_lstnew(NULL);

	ft_lstadd_front(&lst, new);
	printf("addr: %p next: %p\n", new, new->next);
	printf("addr: %p next: %p\n", lst, lst->next);
}
*/
