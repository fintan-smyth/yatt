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

void	print_wordlist(t_word *wordlist, int wordno)
{
	t_word	*cur_word;
	int		word_idx;
	int		i;

	ft_printf("\e[2J\e[H");
	cur_word = wordlist;
	word_idx = 0;
	while (cur_word != NULL)
	{
		i = 0;
		while (i < cur_word->pos)
		{
			if (i < cur_word->len && cur_word->input_buf[i] == cur_word->word[i])
				ft_printf("\e[32;1m%c\e[m", cur_word->input_buf[i]);
			else
				ft_printf("\e[31;1m%c\e[m", cur_word->input_buf[i]);
			i++;
		}
		if (cur_word->pos < cur_word->len)
		{
			if (wordno == word_idx)
			{
				ft_printf("\e[34;1;4m%c\e[m", cur_word->word[i++]);
				ft_printf("\e[34;1m%s\e[m", &cur_word->word[i]);
			}
			else
				ft_printf("%s", &cur_word->word[i]);
		}
		if (cur_word->next != NULL)
			write(1, " ", 1);
		cur_word = cur_word->next;
		word_idx++;
	}
	write(1, "\n", 1);
}

void	print_formatted_key(t_typer *tester, char c)
{
	if (c == tester->c)
	{
		if (tester->is_correct)
			printf("\e[30;42m%c\e[39;49m ", ft_toupper(c));
		else
			printf("\e[30;41m%c\e[39;49m ", ft_toupper(c));
	}
	else
		printf("%c ", ft_toupper(c));
}

void print_keyboard(t_typer *tester)
{
	char	row1[] = "qwertyuiop";
	char	row2[] = "asdfghjkl";
	char	row3[] = "zxcvbnm";
	int		i;;

	printf("\e[1m\n");
	i = -1;
	while (row1[++i])
		print_formatted_key(tester, row1[i]);
	printf("\n ");
	i = -1;
	while (row2[++i])
		print_formatted_key(tester, row2[i]);
	printf("\n  ");
	i = -1;
	while (row3[++i])
		print_formatted_key(tester, row3[i]);
	printf("\n    ");
	if (' ' == tester->c)
	{
		if (tester->is_correct)
			printf("\e[30;42m%s\e[39;49m", "[ SPACE ]");
		else
			printf("\e[30;41m%s\e[39;49m","[ SPACE ]" );
	}
	else
		printf("[ SPACE ]");
	printf("\e[m\n");
}
