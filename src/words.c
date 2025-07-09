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
#include <stdlib.h>

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

void	generate_op_word(char *buf)
{
	int	seed = rand() % OP_MAX;

	switch (seed) {
		case (OP_AND):
			ft_strlcpy(buf, "&&", 128);
			break ;
		case (OP_OR):
			ft_strlcpy(buf, "||", 128);
			break ;
		case (OP_EQ):
			ft_strlcpy(buf, "==", 128);
			break ;
		case (OP_LT):
			ft_strlcpy(buf, "<", 128);
			break ;
		case (OP_GT):
			ft_strlcpy(buf, ">", 128);
			break ;
		case (OP_LTE):
			ft_strlcpy(buf, ">=", 128);
			break ;
		case (OP_GTE):
			ft_strlcpy(buf, "<=", 128);
			break ;
		case (OP_BSLEFT):
			ft_strlcpy(buf, "<<", 128);
			break ;
		case (OP_BSRIGHT):
			ft_strlcpy(buf, "<<", 128);
			break ;
		default:
			break ;
	}
}

void	apply_punc_std(char *word, e_punc punc)
{
	switch (punc) {
		case (P_COMMA):
			ft_strlcat(word, ",", 128);
			break ;
		case (P_FSTOP):
			ft_strlcat(word, ".", 128);
			break ;
		case (P_SQUOTE):
			surround_string(word, "''");
			break ;
		case (P_DQUOTE):
			surround_string(word, "\"\"");
			break ;
		case (P_PAREN):
			surround_string(word, "()");
			break ;
		case (P_BRACK):
			surround_string(word, "[]");
			break ;
		case (P_BRACE):
			surround_string(word, "{}");
			break ;
		case (P_ANGBRACK):
			surround_string(word, "<>");
			break ;
		case (P_EXCLAM):
			ft_strlcat(word, "!", 128);
			break ;
		case (P_QUEST):
			ft_strlcat(word, "?", 128);
			break ;
		default:
			break ;
	}
}

void	apply_punc_clang(char *word, int punc, t_lang *lang)
{
	int		seed = rand() % 2;
	char	buf[128];

	ft_strlcpy(buf, lang->words[rand() % lang->size], 128);
	switch (punc) {
		case (C_STRUCT):
			if (seed)
				ft_strlcat(word, "->", 128);
			else
				ft_strlcat(word, ".", 128);
			ft_strlcat(word, buf, 128);
			break ;
		case (C_FUNC):
			ft_strlcat(word, "(", 128);
			if (seed)
				ft_strlcat(word, buf, 128);
			ft_strlcat(word, ")", 128);
			break ;
		case (C_HEADER):
			ft_strlcat(word, ".h", 128);
			surround_string(word, "<>");
			break ;
		case (C_ARRAY):
			ft_strlcat(word, "[", 128);
			if (seed)
				generate_number_word(buf);
			ft_strlcat(word, buf, 128);
			ft_strlcat(word, "]", 128);
			break ;
		case (C_DEREF):
			surround_string(word, "*");
			break ;
		case (C_ADDR):
			surround_string(word, "&");
			break ;
		case (C_NOT):
			surround_string(word, "!");
			break ;
		case (C_ENDL):
			ft_strlcat(word, ";", 128);
		default:
			break ;
	}
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
		if (tester->options.punc == PMODE_STD)
		{
			if (tester->options.numbers && rand() % 5 == 0)
				generate_number_word(wordnode->word);
			if (tester->options.punc == PMODE_STD
				&& tester->options.punc_flags & (P_MAX - 1)
				&& rand() % 20 < 4)
			{
				int	seed = rand() % 10;
				while (!(tester->options.punc_flags & (1 << seed)))
					seed = rand() % 10;
				apply_punc_std(wordnode->word, (1 << seed));
			}
		}
		if (tester->options.punc == PMODE_CLANG)
		{
			int	seed = rand() % 10;

			if (seed <= 2)
				apply_punc_clang(wordnode->word, rand() % C_MAX, lang);
			else if (seed == 3)
				generate_op_word(wordnode->word);
			else if (seed <= 5 && tester->options.numbers)
				generate_number_word(wordnode->word);
		}
		else if (tester->options.numbers)
		{
			if (tester->options.numbers && rand() % 5 == 0)
				generate_number_word(wordnode->word);
		}
		wordnode->len = ft_strlen(wordnode->word);
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

void	calculate_scroll_vars(t_typer *tester, int *total_lines, int *max_lines, int *cur_word_line)
{
	t_word	*cur_word;
	int		word_idx;
	int		nl_word;
	int		y;
	int		lines;
	int		tmp_max;
	int		tmp_total;
	int		tmp_cur;
	int		last_row;

	last_row = tester->env->win_height - (tester->options.full_keyboard ? 15 : 13);
	cur_word = tester->wordlist;
	tmp_max = 1337;
	tmp_total = 0;
	word_idx = 0;
	nl_word = 0;
	y = 1;
	lines = 0;
	while (cur_word != NULL)
	{
		if (nl_word == word_idx)
		{
			lines++;
			calculate_line_start(tester, cur_word, &nl_word);
			y += 2;
			if (tmp_max == 1337 && y >= last_row)
				tmp_max = lines - 1;
		}
		if (cur_word == tester->cur_word)
			tmp_cur = lines;
		cur_word = cur_word->next;
		word_idx++;
	}
	tmp_total = lines;
	if (tmp_total > tmp_max)
	{
		int	pane_height = tmp_max * 2 + 1;
		int	max_pos = tmp_total - tmp_max;
		int	scroll_pos = clamp_int(((tmp_cur - 2) * pane_height) / max_pos, 0, pane_height - 1);
		// ft_printf("\e[Hscroll_pos %d pane_height %d", scroll_pos, pane_height);
		int	x = tester->env->win_width - 1;
		int	y = -1;

		while (++y < pane_height)
		{
			if (y == scroll_pos)
				ft_printf("\e[%d;%dH\e[44m \e[m", y + 2, x);
			else
				ft_printf("\e[%d;%dH│", y + 2, x);
		}
	}
	*max_lines = tmp_max;
	*cur_word_line = tmp_cur;
	*total_lines = tmp_total;
}

int	print_wordlist(t_typer *tester)
{
	t_word	*cur_word;
	int		word_idx;
	int		nl_word;
	int		x;
	int		y;
	int		line;
	int		max_lines;
	int		total_lines;
	int		cur_word_line;
	int		print;
	// int		last_frame;

	cur_word = tester->wordlist;
	calculate_scroll_vars(tester, &total_lines, &max_lines, &cur_word_line);
	// last_frame = total_lines - max_lines + 2;
	// exit(0);
	word_idx = 0;
	nl_word = 0;
	y = 1;
	line = 0;
	print = 0;
	while (cur_word != NULL)
	{
		if (nl_word == word_idx)
		{
			line++;
			if (line >= (cur_word_line == 1 ? 2 : cur_word_line) + max_lines - 1)
				break ;
			if (print == 0 && (line >= cur_word_line - 1 || line + max_lines > total_lines))
				print = 1;
			x = calculate_line_start(tester, cur_word, &nl_word);
			if (print)
				y += 2;
			ft_printf("\e[%d;%dH", y, x);
		}
		if (print)
			print_word(cur_word, word_idx, tester->cur_word_idx);
		cur_word = cur_word->next;
		word_idx++;
	}
	// ft_printf("\ntotal: %d max: %d cur_word: %d", total_lines, max_lines, cur_word_line);
	write(1, "\n", 1);
	return (y + 2);
}
