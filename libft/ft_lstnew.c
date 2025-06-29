/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:39:46 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/30 14:33:08 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = content;
	return (new);
}
/*
int	main(void)
{
	char	*s = "test string";
	t_list	*node;

	node = ft_lstnew(s);
	printf("content: %s\nnext: %p\n", (char *)node->content, node->next);
}
*/
