/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:15:02 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/02 00:53:10 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <ncurses.h>
#include <stdio.h>

void	check_input(t_typer *tester, char c, t_word *cur_word)
{
	tester->is_correct = 1;
	if (c == ' ')
	{
		if (ft_strcmp(cur_word->input_buf, cur_word->word) != 0)
		{
			tester->incorrect_inputs++;
			tester->is_correct = 0;
		}
	}
	else if (ft_strncmp(cur_word->input_buf, cur_word->word, ft_strlen(cur_word->input_buf)) != 0)
	{
		tester->incorrect_inputs++;
		tester->is_correct = 0;
	}
}

double	calculate_raw_wpm(t_typer *tester)
{
	size_t	time_diff;
	double	minutes;
	double	words_typed;

	time_diff = tester->end_time - tester->start_time;
	if (time_diff == 0)
		return (0);
	minutes = time_diff / (60000.0);
	words_typed = tester->inputs_count / 5.0;
	return (words_typed / minutes);
}

int	count_errors(t_typer *tester)
{
	t_word	*cur_word;
	int		word_idx;
	int		errors;

	cur_word = tester->wordlist;
	errors = 0;
	word_idx = 0;
	while (cur_word != NULL && word_idx <= tester->cur_word_idx)
	{
		if (ft_strcmp(cur_word->input_buf, cur_word->word) != 0)
			errors++;
		cur_word = cur_word->next;
		word_idx++;
	}
	return (errors);
}

double	calculate_net_wpm(t_typer *tester)
{
	size_t	time_diff;
	double	minutes;
	double	words_typed;
	int		errors;
	double	wpm;

	time_diff = tester->end_time - tester->start_time;
	minutes = time_diff / (60000.0);
	words_typed = tester->inputs_count / 5.0;
	errors = count_errors(tester);
	// printf("\e[31m<<errors: %d words_typed: %.1f minutes: %.1f>>\e[m\n", errors, words_typed, minutes);
	wpm = (words_typed - errors) / minutes;
	if (wpm < 0)
		wpm = 0;
	return (wpm);
}

double	calculate_adj_wpm(t_typer *tester)
{
	size_t	time_diff;
	double	minutes;
	double	words_typed;

	time_diff = tester->end_time - tester->start_time;
	if (time_diff == 0)
		return (0);
	minutes = time_diff / (60000.0);
	words_typed = (tester->inputs_count - tester->incorrect_inputs) / 5.0;
	return (words_typed / minutes);
}

double	calculate_accuracy(t_typer *tester)
{
	if (tester->inputs_count == 0)
		return (0);
	return (((double)tester->inputs_count - tester->incorrect_inputs) / tester->inputs_count);
}

void	print_adj_wpm(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "Adj WPM: %.1f", calculate_adj_wpm(tester));
	// print_str_centred(buf, line, tester->env->win_width);
	centre_str(buf, line, tester->env->win_width);
	attrset(A_BOLD | COLOR_PAIR(MAGENTA_FG));
	addstr("Adj WPM");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	printw(": %.1f", calculate_adj_wpm(tester));
}

void	print_net_wpm(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "Net WPM: %.1f", calculate_net_wpm(tester));
	// print_str_centred(buf, line, tester->env->win_width);
	centre_str(buf, line, tester->env->win_width);
	attrset(A_BOLD | COLOR_PAIR(MAGENTA_FG));
	addstr("Net WPM");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	printw(": %.1f", calculate_net_wpm(tester));
}

void	print_raw_wpm(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "Raw WPM: %.1f", calculate_raw_wpm(tester));
	// print_str_centred(buf, line, tester->env->win_width);
	centre_str(buf, line, tester->env->win_width);
	attrset(A_BOLD | COLOR_PAIR(MAGENTA_FG));
	addstr("Raw WPM");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	printw(": %.1f", calculate_raw_wpm(tester));
}

void	print_accuracy(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "Accuracy: %.1f%%", calculate_accuracy(tester) * 100);
	// print_str_centred(buf, line, tester->env->win_width);
	centre_str(buf, line, tester->env->win_width);
	attrset(A_BOLD | COLOR_PAIR(YELLOW_FG));
	addstr("Accuracy");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	printw(": %.1f%%", calculate_accuracy(tester) * 100);
}

void	print_correct_inputs(t_typer *tester, int line)
{
	char	buf[256];
	
	ft_snprintf(buf, 256, "Correct inputs: %d/%d", tester->inputs_count - tester->incorrect_inputs, tester->inputs_count);
	// print_str_centred(buf, line, tester->env->win_width);
	centre_str(buf, line, tester->env->win_width);
	attrset(A_BOLD | COLOR_PAIR(YELLOW_FG));
	addstr("Correct inputs");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	printw(": %d/%d", tester->inputs_count - tester->incorrect_inputs, tester->inputs_count);
}

void	print_retry_message(t_typer *tester, int line)
{
	attrset(A_BOLD | A_ITALIC | COLOR_PAIR(DEFAULT_COLS));
	centre_str("Press 'R' to retry, 'Q' to quit,", ++line, tester->env->win_width);
	addstr("Press '");
	addch('R' | COLOR_PAIR(GREEN_FG));
	addstr("' to retry, '");
	addch('Q' | COLOR_PAIR(RED_FG));
	addstr("' to quit,");
	centre_str("or 'O' for options", line + 1, tester->env->win_width);
	addstr("or '");
	addch('O' | COLOR_PAIR(BLUE_FG));
	addstr("' for options");
}

void	print_stats(t_typer *tester, int line)
{
	line += 2;
	print_adj_wpm(tester, line++);
	print_net_wpm(tester, line++);
	print_raw_wpm(tester, line++);
	print_accuracy(tester, ++line);
	print_correct_inputs(tester, ++line);
	line++;
	print_retry_message(tester, line);
}

void	render_stats(t_typer *tester)
{
	int		line;
	cchar_t	*boxchars = tester->boxchars;

	erase();
	draw_borders(tester);
	line = print_wordlist(tester);
	// ft_printf("\e[%d;1H├", line);
	// i = 2;
	// while (i++ < tester->env->win_width)
	// 	ft_putstr_fd("─", 1);
	// ft_putstr_fd("┤", 1);
	mvadd_wch(line, 0, &boxchars[6]);
	hline_set(&boxchars[1], tester->env->win_width - 2);
	mvadd_wch(line, tester->env->win_width - 1, &boxchars[7]);
	print_stats(tester, line);
	refresh();
}

int	stats_screen(t_typer *tester)
{
	char	c;

	c = 0;
	while (1)
	{
		if (c == ESC || c == 'q')
			return (1);
		else if (c == 'r')
			return (0);
		else if (c == 'o')
			exec_render_func(tester, render_options);
		exec_render_func(tester, render_stats);
		c = ft_tolower(getchar_nb(tester, render_stats));
	}
}
