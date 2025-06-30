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

int	wordnode_exists(t_word *wordlist, char *word)
{
	t_word	*cur_word;

	cur_word = wordlist;
	while (cur_word != NULL)
	{
		if (cur_word->word == word)
			return (1);
		cur_word = cur_word->next;
	}
	return (0);
}

void	select_words(t_typer *tester)
{
	unsigned int		i = 0;
	unsigned int		num_words = tester->num_words;
	int					index;
	char				*word;
	t_lang				*lang = &tester->lang;

	while (i < num_words)
	{
		index = rand() % lang->size;
		word = lang->words[index];
		if (i < lang->size && wordnode_exists(tester->wordlist, word))
			continue ;
		wordlist_add_back(&tester->wordlist, new_wordnode(word));
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
			ft_printf("\e[%d;H│\e[B\e[D│\e[%dG│\e[%d;%dH│\e[%d;%dH",
				y, tester->env->win_width,
				y, tester->env->win_width,
				y, x);
		}
		print_word(cur_word, word_idx, tester->cur_word_idx);
		cur_word = cur_word->next;
		word_idx++;
	}
	write(1, "\n", 1);
	return (y + 2);
}

void	print_formatted_key(t_typer *tester, char c)
{
	if (c == tester->c)
	{
		if (tester->is_correct)
			ft_printf("\e[30;42m %c \e[39;49m", ft_toupper(c));
		else
			ft_printf("\e[30;41m %c \e[39;49m", ft_toupper(c));
	}
	else
		ft_printf(" %c ", ft_toupper(c));
	ft_putstr_fd("│", 1);
}

int print_keyboard(t_typer *tester, int y)
{
	char	row1[] = "qwertyuiop";
	char	row2[] = "asdfghjkl";
	char	row3[] = "zxcvbnm";
	char	space[] = "     SPACE     ";
	int		i;
	int		line_start;

	line_start = (tester->env->win_width - 41) / 2 + 1;
	y += 3;
	ft_printf("\e[1m\e[%d;%dH┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐", y++, line_start);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row1[++i])
		print_formatted_key(tester, row1[i]);
	ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘", y++, line_start++);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row2[++i])
		print_formatted_key(tester, row2[i]);
	ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┘", y++, line_start++);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row3[++i])
		print_formatted_key(tester, row3[i]);
	ft_printf("\e[%d;%dH└───┴───┴┬──┴───┴───┴───┴┬──┘", y++, line_start);
	line_start += 9;
	ft_printf("\e[%d;%dH", y++, line_start);
	if (' ' == tester->c && tester->is_correct >= 0)
	{
		if (tester->is_correct)
			ft_printf("│\e[30;42m%s\e[39;49m│", space);
		else
			ft_printf("│\e[30;41m%s\e[39;49m│", space);
	}
	else
		ft_printf("│%s│", space);
	ft_printf("\e[%d;%dH└───────────────┘", y++, line_start);
	ft_printf("\e[m\n");
	return (y);
}
