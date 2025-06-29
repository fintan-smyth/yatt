/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:57:14 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/27 20:15:21 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*test_func(void *content)
{
	int		*num = malloc(sizeof(int));

	*num = *(int *)content;
	*num += 5;
	return (num);
}
*/

static int	map_node(t_list *lst, t_list *new_list,
					void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*new;

	new_content = f(lst->content);
	new = ft_lstnew(new_content);
	if (new == NULL)
	{
		ft_lstclear(&new_list, del);
		del(new_content);
		return (0);
	}
	ft_lstadd_back(&new_list, new);
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	void	*new_content;

	if (lst == NULL)
		return (NULL);
	new_content = f(lst->content);
	new_list = ft_lstnew(new_content);
	if (new_list == NULL)
	{
		del(new_content);
		return (NULL);
	}
	lst = lst->next;
	while (lst != NULL)
	{
		if (!map_node(lst, new_list, f, del))
			return (NULL);
		lst = lst->next;
	}
	return (new_list);
}
/*
int	main(void)
{
	int		n1 = 10;
	int		n2 = 11;
	t_list	*original = ft_lstnew((void *)&n1);
	t_list	*new;
	t_list	*current;

	ft_lstadd_back(&original, ft_lstnew((void *)&n2));
	current = original;
	printf("original\n");
	while (current != NULL)
	{
		printf("<addr: %p> <next: %p> <content: %d>\n",
	   	current, current->next, *(int *)current->content);
		current = current->next;
	}

	new = ft_lstmap(original, test_func, NULL);
	current = new;
	printf("\nmapped\n");
	while (current != NULL)
	{
		printf("<addr: %p> <next: %p> <content: %d>\n",
	   	current, current->next, *(int *)current->content);
		current = current->next;
	}
}
*/
