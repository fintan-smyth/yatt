/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:15:02 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/29 17:47:56 by fsmyth           ###   ########.fr       */
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
	printf("\e[31m<<errors: %d words_typed: %.1f minutes: %.1f>>\e[m\n", errors, words_typed, minutes);
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
	double	acc;

	time_diff = tester->end_time - tester->start_time;
	minutes = time_diff / (60000.0);
	words_typed = tester->inputs_count / 5.0;
	acc = calculate_accuracy(tester);
	return (acc * words_typed / minutes);
}

double	calculate_accuracy(t_typer *tester)
{
	return (((double)tester->inputs_count - tester->incorrect_inputs) / tester->inputs_count);
}

int	display_stats(t_typer *tester)
{
	char	c;

	print_wordlist(tester);
	printf("\n");
	printf("\e[35;1mAdj WPM\e[m:\t%.1f\n", calculate_adj_wpm(tester));
	printf("\e[35;1mNet WPM\e[m:\t%.1f\n", calculate_net_wpm(tester));
	printf("\e[35;1mRaw WPM\e[m:\t%.1f\n\n", calculate_raw_wpm(tester));
	printf("\e[33;1mAccuracy\e[m:\t%.1f%%\n", calculate_accuracy(tester) * 100);
	printf("\e[33;1mCorrect inputs\e[m:\t%d/%d\n", tester->inputs_count - tester->incorrect_inputs, tester->inputs_count);
	printf("\n\e[1;3mPress '\e[32mR\e[39m' to retry or '\e[31mQ\e[39m' to quit\e[m\n");
	c = ft_tolower(getchar());
	while (1)
	{
		if (c == ESC || c == 'q')
			return (1);
		else if (c == 'r')
			return (0);
		c = getchar();
	}
}
