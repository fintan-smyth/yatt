/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:33:41 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/03 19:39:44 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

t_word	*new_wordnode(char *str)
{
	t_word	*wordnode;

	wordnode = ft_calloc(1, sizeof(*wordnode));
	ft_strlcpy(wordnode->word, str, 128);
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

int	wordnode_exists(t_word *wordlist, char *word)
{
	t_word	*cur_word;

	cur_word = wordlist;
	while (cur_word != NULL)
	{
		if (ft_strcmp(cur_word->word, word) == 0)
			return (1);
		cur_word = cur_word->next;
	}
	return (0);
}

void	generate_number_word(char *buf)
{
	int	seed;
	int	len;
	int	i;

	seed = rand() % 3;
	len = seed + 2;
	i = 0;
	while (i < len)
	{
		buf[i] = rand() % 10 + '0';
		i++;
	}
	buf[i] = 0;
}

void	select_words(t_typer *tester)
{
	unsigned int		i = 0;
	unsigned int		num_words = tester->options.num_words;
	int					index;
	char				*word;
	t_lang				*lang = &tester->lang;
	t_word				*wordnode;

	while (i < num_words)
	{
		index = rand() % lang->size;
		word = lang->words[index];
		if (i < lang->size && wordnode_exists(tester->wordlist, word))
			continue ;
		wordnode = wordlist_add_back(&tester->wordlist, new_wordnode(word));
		if (tester->options.punc || tester->options.numbers)
		{
			int	seed = rand() % 20;

			if (tester->options.numbers && rand() % 5 == 0)
				generate_number_word(wordnode->word);
			if (tester->options.punc)
			{
				if (seed < 2)
					ft_strlcat(wordnode->word, ",", 128);
				else if (seed < 4)
					ft_strlcat(wordnode->word, ".", 128);
			}
			wordnode->len = ft_strlen(wordnode->word);
		}
		i++;
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
	int		len;

	width = tester->env->win_width - 4;
	char_count = 0;
	cur_word = first_word;
	word_count = *nl_word;
	while (cur_word != NULL)
	{
		len = max_int(cur_word->pos, cur_word->len);
		if (char_count + len + 1 >= width)
			break ;
		word_count++;
		char_count += len + 1;
		cur_word = cur_word->next;
	}
	start = (1 + width - char_count) / 2 + 3;
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

	cur_word = tester->wordlist;
	word_idx = 0;
	nl_word = 0;
	y = 1;
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
	return (y + 2);
}
