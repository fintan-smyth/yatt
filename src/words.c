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
#include <curses.h>
#include <ncurses.h>
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

void	apply_punc_std(t_typer *tester, char *word, int punc)
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
	(void)tester;
}

void	apply_punc_clang(t_typer *tester, char *word, int punc)
{
	int		seed = rand() % 10;
	char	buf[128];
	t_lang	*lang = &tester->lang;

	ft_strlcpy(buf, lang->words[rand() % lang->size], 128);
	switch (punc) {
		case (C_STRUC_ARROW):
			ft_strlcat(word, "->", 128);
			ft_strlcat(word, buf, 128);
			break ;
		case (C_STRUC_DOT):
			ft_strlcat(word, ".", 128);
			ft_strlcat(word, buf, 128);
			break ;
		case (C_FUNC):
			ft_strlcat(word, "(", 128);
			if (seed < 5)
				ft_strlcat(word, buf, 128);
			ft_strlcat(word, ")", 128);
			break ;
		case (C_HEADER):
			ft_strlcat(word, ".h", 128);
			surround_string(word, "<>");
			break ;
		case (C_ARRAY):
			ft_strlcat(word, "[", 128);
			if (tester->options.numbers && seed < 7)
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
			break ;
		case (C_AND):
			ft_strlcpy(word, "&&", 128);
			break ;
		case (C_OR):
			ft_strlcpy(word, "||", 128);
			break ;
		case (C_EQ):
			ft_strlcpy(word, "==", 128);
			break ;
		case (C_LT):
			ft_strlcpy(word, "<", 128);
			break ;
		case (C_GT):
			ft_strlcpy(word, ">", 128);
			break ;
		case (C_LTE):
			ft_strlcpy(word, ">=", 128);
			break ;
		case (C_GTE):
			ft_strlcpy(word, "<=", 128);
			break ;
		case (C_BSLEFT):
			ft_strlcpy(word, "<<", 128);
			break ;
		case (C_BSRIGHT):
			ft_strlcpy(word, ">>", 128);
			break ;
		case (C_PREINC):
			prefix_string(word, "++");
			break ;
		case (C_PREDEC):
			prefix_string(word, "++");
			break ;
		case (C_POSTINC):
			ft_strlcat(word, "++", 128);
			break ;
		case (C_POSTDEC):
			ft_strlcat(word, "--", 128);
			break ;
		default:
			break ;
	}
}

int	pick_punc(t_punc *punc)
{
	int	cum_weights;
	int	punc_code;
	int	seed = rand() % punc->sum_weights;

	punc_code = -1;
	cum_weights = 0;
	do {
		punc_code++;
		cum_weights += punc->weights[punc_code];
	}
	while (cum_weights <= seed);
	// ft_dprintf(2, "\nseed: %d cum_weights %d code %d\n", seed, cum_weights, punc_code);
	// exit(0);
	return (punc_code);
}

void	apply_punc(t_typer *tester, char *word)
{
	int		seed;
	t_punc	*punc;
	void	(*punc_func)(t_typer *, char *, int);

	if (tester->options.punc == PMODE_STD)
	{
		punc = &tester->options.standard;
		punc_func = apply_punc_std;
	}
	else if (tester->options.punc == PMODE_CLANG)
	{
		punc = &tester->options.clang;
		punc_func = apply_punc_clang;
	}
	else
		return ;
	seed = rand() % 100;
	if (seed < punc->prob)
		punc_func(tester, word, pick_punc(punc));
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
		if (tester->options.numbers && tester->options.punc != PMODE_CLANG)
		{
			if (rand() % 100 < tester->options.number_prob)
				generate_number_word(wordnode->word);
		}
		apply_punc(tester, wordnode->word);
		wordnode->len = ft_strlen(wordnode->word);
		i++;
	}
}

// void	select_words(t_typer *tester)
// {
// 	unsigned int		i = 0;
// 	unsigned int		num_words = tester->options.num_words;
// 	int					index;
// 	char				*word;
// 	t_lang				*lang = &tester->lang;
// 	t_word				*wordnode;
// 	t_punc				*punc;
//
// 	while (i < num_words)
// 	{
// 		index = rand() % lang->size;
// 		word = lang->words[index];
// 		if (i < lang->size && wordnode_exists(tester->wordlist, word))
// 			continue ;
// 		wordnode = wordlist_add_back(&tester->wordlist, new_wordnode(word));
// 		if (tester->options.punc == PMODE_STD)
// 		{
// 			if (tester->options.numbers && rand() % 5 == 0)
// 				generate_number_word(wordnode->word);
// 			{
// 				int	seed = rand() % 10;
// 				while (!(tester->options.punc_flags & (1 << seed)))
// 					seed = rand() % 10;
// 				apply_punc_std(wordnode->word, (1 << seed));
// 			}
// 		}
// 		if (tester->options.punc == PMODE_CLANG)
// 		{
// 			punc = &tester->options.clang;
// 			int	seed = rand() % 10;
//
// 			if (seed < punc->prob)
// 				apply_punc_clang(wordnode->word, pick_punc(punc), lang);
// 			// else if (seed == 3)
// 			// 	generate_op_word(wordnode->word);
// 			// else if (seed <= 5 && tester->options.numbers)
// 			// 	generate_number_word(wordnode->word);
// 		}
// 		else if (tester->options.numbers)
// 		{
// 			if (tester->options.numbers && rand() % 5 == 0)
// 				generate_number_word(wordnode->word);
// 		}
// 		wordnode->len = ft_strlen(wordnode->word);
// 		i++;
// 	}
// }

void	print_word(t_word *cur_word, int word_idx, int cur_word_idx)
{
	int	i;
	int	x, y;

	i = 0;
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	while (i < cur_word->pos)
	{
		if (cur_word_idx == word_idx)
			attron(A_BOLD);
		if (i < cur_word->len && cur_word->input_buf[i] == cur_word->word[i])
			// printw("\e[32;1m%c\e[m", cur_word->word[i]);
			addch(cur_word->word[i] | COLOR_PAIR(GREEN_FG));
		else
		{
			addch((i < cur_word->len ? cur_word->word[i] : cur_word->input_buf[i]) | COLOR_PAIR(RED_FG));
			getyx(stdscr, y, x);
			attrset(A_ITALIC | COLOR_PAIR(DEFAULT_COLS));
			mvaddch(y + 1, x - 1, cur_word->input_buf[i]);
			move(y, x);
			// printw("\e[B\e[D\e[3m%c\e[m\e[A", cur_word->input_buf[i]);
		}
		i++;
	}
	if (cur_word->pos < cur_word->len)
	{
		if (cur_word_idx == word_idx)
		{
			attron(COLOR_PAIR(BLUE_FG) | A_BOLD);
			addch(cur_word->word[i++] | A_UNDERLINE);
			// printw("\e[34;1;4m%c\e[m", cur_word->word[i++]);
			addstr(&cur_word->word[i]);
		}
		else
		{
			attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
			printw("%s", &cur_word->word[i]);
		}
	}
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	if (cur_word->next != NULL)
		// write(1, " ", 1);
		addch(' ');
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
	start = (1 + width - char_count) / 2 + 2;
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
		int	x = tester->env->win_width - 2;
		int	y = -1;

		while (++y < pane_height)
		{
			if (y == scroll_pos)
			{
				attrset(COLOR_PAIR(BLUE_BG));
				mvprintw(y + 1, x, " ");
			}
			else
				mvprintw(y + 1, x, "│");
			attrset(A_NORMAL);
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
	y = 0;
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
			// ft_printf("\e[%d;%dH", y, x);
			move(y, x);
		}
		if (print)
			print_word(cur_word, word_idx, tester->cur_word_idx);
		cur_word = cur_word->next;
		word_idx++;
	}
	// ft_printf("\ntotal: %d max: %d cur_word: %d", total_lines, max_lines, cur_word_line);
	// write(1, "\n", 1);
	return (y + 2);
}
