/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:23:49 by fsmyth            #+#    #+#             */
/*   Updated: 2025/08/28 13:11:45 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <locale.h>

void	inplog_add_back(t_inplog **head, t_inplog *node)
{
	if (head == NULL)
		return ;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	t_inplog *current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void	log_input(t_typer *tester, char c, t_word *word, size_t *timestamp)
{
	if (!ft_isprint(c) && c != BACKSPACE)
		return ;

	t_inplog	*new = ft_calloc(1, sizeof(*new));
	size_t		time;

	time = get_time_ms();
	new->time_per_key = time - *timestamp;
	*timestamp = time;
	new->time = time;
	new->input = c;
	if (word->pos >= word->len)
		new->expected = ' ';
	else
		new->expected = word->word[word->pos];
	inplog_add_back(&tester->inplog, new);
}

void	print_inplog(t_typer *tester)
{
	t_inplog	*current;
	size_t		start;

	current = tester->inplog;
	start = current->time;
	while (current != NULL)
	{
		if (current->input == BACKSPACE)
			printf("%ld\tinput: <BKSPC>\texpected: <%c> time_per_key: %ld\n", current->time - start, current->expected, current->time_per_key);
		else
			printf("%ld\tinput:   <%c>\texpected: <%c> time_per_key: %ld\n", current->time - start, current->input, current->expected, current->time_per_key);
		current = current->next;
	}
}

void	clear_inplog(t_inplog **head)
{
	t_inplog *current;
	t_inplog *temp;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}
