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
#include <stdio.h>

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
	if (current == NULL)
		return ;
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

void	add_inpstat_node(t_tree **root, t_inplog *log)
{
	t_tree		*current;
	t_tree		**addr;
	t_inpstat	*statnode;

	if (root == NULL)
		return ;
	current = *root;
	addr = root;
	while (current != NULL)
	{
		statnode = current->content;
		if (log->expected > statnode->c)
			addr = &current->right;
		else if (log->expected < statnode->c)
			addr = &current->left;
		else
			break ;
		current = *addr;
	}
	if (current == NULL)
	{
		statnode = ft_calloc(1, sizeof(*statnode));
		statnode->c = log->expected;
		current = ft_tree_new(statnode);
		*addr = current;
	}
	statnode->total++;
	if (statnode->c == log->input)
	{
		statnode->total_correct++;
		statnode->total_time += log->time_per_key;
		statnode->avg_time = (double)statnode->total_time / statnode->total_correct;
		statnode->accuracy = (double)statnode->total_correct / statnode->total;
	}
}

t_tree	*build_inpstat_tree(t_inplog *head)
{
	t_tree		*out = NULL;
	t_inplog	*current;

	if (head == NULL || head->next == NULL)
		return (NULL);
	for (current = head->next; current != NULL; current = current->next)
	{
		if (current->input == BACKSPACE || current->expected == ' ')
			continue ;
		add_inpstat_node(&out, current);
	}
	return (out);
}

void	get_keystats(t_tree *node, t_keystats *stats)
{
	t_inpstat	*cur_log = node->content;
	
	if (stats->least_acc == NULL)
		stats->least_acc = cur_log;
	else if (cur_log->accuracy < stats->least_acc->accuracy)
		stats->least_acc = cur_log;

	if (stats->slowest == NULL)
		stats->slowest = cur_log;
	else if (cur_log->avg_time > stats->slowest->avg_time)
		stats->slowest = cur_log;
}

void	reorder_tree_avgtime(t_tree *node, t_tree **root)
{
	t_tree		**addr;
	t_tree		*current;
	t_inpstat	*to_place;
	t_inpstat	*cur_stat;

	current = *root;
	addr = root;
	to_place = node->content;
	while (current != NULL)
	{
		cur_stat = current->content;
		if (to_place->avg_time < cur_stat->avg_time)
			addr = &current->left;
		else
			addr = &current->right;
		current = *addr;
	}
	*addr = node;
	node->left = NULL;
	node->right = NULL;
}

void	reorder_tree_acc(t_tree *node, t_tree **root)
{
	t_tree		**addr;
	t_tree		*current;
	t_inpstat	*to_place;
	t_inpstat	*cur_stat;

	current = *root;
	addr = root;
	to_place = node->content;
	while (current != NULL)
	{
		cur_stat = current->content;
		if (to_place->accuracy < cur_stat->accuracy)
			addr = &current->left;
		else
			addr = &current->right;
		current = *addr;
	}
	*addr = node;
	node->left = NULL;
	node->right = NULL;
}

t_tree	*reorder_tree(t_tree *root, void (*f)(void *, void *))
{
	t_tree *out = NULL;

	ft_traverse_tree(root, PST_ORD, f, &out);
	return (out);
}

void	print_inpstat(t_tree *treenode, void *data)
{
	t_inpstat	*statnode = treenode->content;
	printf("char: %c\t total_time: %4ldms  correct: %2ld/%2ld  avg_time: %.1fms\tacc: %.1f%%\n", 
		statnode->c, statnode->total_time, statnode->total_correct, statnode->total, statnode->total_time / (double)statnode->total_correct, statnode->total_correct / (double)statnode->total * 100);
	(void)data;
}
