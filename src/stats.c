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
	
	snprintf(buf, 256, "\e[35;1mAdj WPM\e[m: %.1f", calculate_adj_wpm(tester));
	print_str_centred(buf, line, tester->env->win_width);
}

void	print_net_wpm(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "\e[35;1mNet WPM\e[m: %.1f", calculate_net_wpm(tester));
	print_str_centred(buf, line, tester->env->win_width);
}

void	print_raw_wpm(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "\e[35;1mRaw WPM\e[m: %.1f", calculate_raw_wpm(tester));
	print_str_centred(buf, line, tester->env->win_width);
}

void	print_accuracy(t_typer *tester, int line)
{
	char	buf[256];
	
	snprintf(buf, 256, "\e[33;1mAccuracy\e[m: %.1f%%", calculate_accuracy(tester) * 100);
	print_str_centred(buf, line, tester->env->win_width);
}

void	print_correct_inputs(t_typer *tester, int line)
{
	char	buf[256];
	
	ft_snprintf(buf, 256, "\e[33;1mCorrect inputs\e[m: %d/%d", tester->inputs_count - tester->incorrect_inputs, tester->inputs_count);
	print_str_centred(buf, line, tester->env->win_width);
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
	print_str_centred("\e[1;3mPress '\e[32mR\e[39m' to retry, '\e[31mQ\e[39m' to quit,\e[m", ++line, tester->env->win_width);
	print_str_centred("\e[1;3mor '\e[34mO\e[39m' for options\e[m", line + 1, tester->env->win_width);
}

void	render_stats(t_typer *tester)
{
	int	line;
	int	i;

	draw_borders(tester);
	line = print_wordlist(tester);
	ft_printf("\e[%d;1H├", line);
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("┤", 1);
	return (print_stats(tester, line));
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
