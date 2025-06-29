/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:33:41 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/29 17:56:34 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

t_word	*new_wordnode(char *str)
{
	t_word	*wordnode;

	wordnode = ft_calloc(1, sizeof(*wordnode));
	wordnode->word = str;
	wordnode->len = ft_strlen(str);
	return (wordnode);
}

t_word	*wordlist_add_back(t_word **lst, t_word *word)
{
	t_word	*current;

	if (lst == NULL)
		return (word);
	if (*lst == NULL)
	{
		*lst = word;
		return (word);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = word;
	word->prev = current;
	return (word);
}

void	clear_wordlist(t_word **wordlist)
{
	t_word	*current;
	t_word	*tmp;

	current = *wordlist;
	while (current != NULL)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*wordlist = NULL;
}

void	select_words(t_typer *tester)
{
	int		i = -1;
	int		index;
	int		num_words = tester->num_words;
	t_lang	*lang = &tester->lang;

	while (++i < num_words)
	{
		index = rand() % lang->size;
		wordlist_add_back(&tester->wordlist, new_wordnode(lang->words[index]));
	}
}

void	print_word(t_word *cur_word, int word_idx, int cur_word_idx)
{
	int	i;

	i = 0;
	while (i < cur_word->pos)
	{
		if (i < cur_word->len && cur_word->input_buf[i] == cur_word->word[i])
			ft_printf("\e[32;1m%c\e[m", cur_word->word[i]);
		else
		{
			ft_printf("\e[31;1m%c\e[m", i < cur_word->len ? cur_word->word[i] : cur_word->input_buf[i]);
			ft_printf("\e[B\e[D\e[3m%c\e[m\e[A", cur_word->input_buf[i]);
		}
		i++;
	}
	if (cur_word->pos < cur_word->len)
	{
		if (cur_word_idx == word_idx)
		{
			ft_printf("\e[34;1;4m%c\e[m", cur_word->word[i++]);
			ft_printf("\e[34;1m%s\e[m", &cur_word->word[i]);
		}
		else
			ft_printf("%s", &cur_word->word[i]);
	}
	if (cur_word->next != NULL)
		write(1, " ", 1);
}

int	calculate_line_start(t_typer *tester, t_word *first_word, int *nl_word)
{
	t_word	*cur_word;
	int		width;
	int		char_count;
	int		word_count;
	int		start;

	width = tester->env->win_width;
	char_count = 0;
	cur_word = first_word;
	word_count = *nl_word;
	while (cur_word != NULL)
	{
		if (char_count + cur_word->len + 1 >= width)
			break ;
		word_count++;
		char_count += cur_word->len + 1;
		cur_word = cur_word->next;
	}
	start = (1 + width - char_count) / 2 + 1;
	*nl_word = word_count;
	return (start);
}

int	print_wordlist(t_typer *tester)
{
	t_word	*cur_word;
	int		word_idx;
	int		nl_word;
	int		x;
	int		y;

	ft_printf("\e[2J\e[H");
	cur_word = tester->wordlist;
	word_idx = 0;
	nl_word = 0;
	y = 0;
	while (cur_word != NULL)
	{
		if (nl_word == word_idx)
		{
			x = calculate_line_start(tester, cur_word, &nl_word);
			y += 2;
			ft_printf("\e[%d;%dH", y, x);
		}
		print_word(cur_word, word_idx, tester->cur_word_idx);
		cur_word = cur_word->next;
		word_idx++;
	}
	write(1, "\n", 1);
	return (y);
}

void	print_formatted_key(t_typer *tester, char c)
{
	if (c == tester->c)
	{
		if (tester->is_correct)
			ft_printf("\e[30;42m%c\e[39;49m ", ft_toupper(c));
		else
			ft_printf("\e[30;41m%c\e[39;49m ", ft_toupper(c));
	}
	else
		ft_printf("%c ", ft_toupper(c));
}

void print_keyboard(t_typer *tester, int y)
{
	char	row1[] = "qwertyuiop";
	char	row2[] = "asdfghjkl";
	char	row3[] = "zxcvbnm";
	int		i;
	int		line_start;

	line_start = tester->env->win_width / 2 - 9;
	y += 3;
	ft_printf("\e[1m\e[%d;%dH", y++, line_start++);
	i = -1;
	while (row1[++i])
		print_formatted_key(tester, row1[i]);
	ft_printf("\e[1m\e[%d;%dH", y++, line_start++);
	i = -1;
	while (row2[++i])
		print_formatted_key(tester, row2[i]);
	ft_printf("\e[1m\e[%d;%dH", y++, line_start++);
	i = -1;
	while (row3[++i])
		print_formatted_key(tester, row3[i]);
	ft_printf("\e[1m\e[%d;%dH", y++, ++line_start);
	if (' ' == tester->c)
	{
		if (tester->is_correct)
			ft_printf("\e[30;42m%s\e[39;49m", "[ SPACE ]");
		else
			ft_printf("\e[30;41m%s\e[39;49m","[ SPACE ]" );
	}
	else
		ft_printf("[ SPACE ]");
	ft_printf("\e[m\n");
}
