/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:11:43 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/24 20:09:05 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <fcntl.h>

t_list	*read_file(char *filename)
{
	int		fd;
	char	*line;
	t_list	*lines;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
		ft_lstadd_back(&lines, ft_lstnew(line));
	close(fd);
	return (lines);
}

void	strip_comments_and_empty(t_list **lines)
{
	t_list	*current;
	char	*comment_start;

	current = *lines;
	while (current != NULL)
	{
		if ((comment_start = ft_strchr(current->str, '#')) != NULL)
			*comment_start = '\0';
		current = current->next;
	}

	current = *lines;
	while (ft_strwhitespace(current->str))
	{
		*lines = current->next;
		ft_lstdelone(current, free);
		current = *lines;
		if (current == NULL)
			return ;
	}
	while (current->next != NULL)
	{
		if (ft_strwhitespace(current->next->str))
		{
			ft_lstdel_next(current, free);
			continue ;
		}
		current = current->next;
	}
}

int	parse_config(t_typer *tester, char *filename)
{
	t_list	*lines;
	t_list	*current;

	lines = read_file(filename);
	strip_comments_and_empty(&lines);
	// cleanup(tester);
	// current = lines;
	// while (current != NULL)
	// {
	// 	printf("<%s>", current->str);
	// 	current = current->next;
	// }
	ft_lstclear(&lines, free);
	return (0);
}
