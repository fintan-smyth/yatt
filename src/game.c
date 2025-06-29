/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:39:56 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/29 17:25:17 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"

void	reset_game(t_typer *tester)
{
	select_words(tester);
	tester->inputs_count = 0;
	tester->cur_word_idx = 0;
	tester->incorrect_inputs = 0;
	tester->c = 0;
}

void	run_game(t_typer *tester)
{
	t_word	*cur_word;
	int		line;

	reset_game(tester);
	cur_word = tester->wordlist;
	line = print_wordlist(tester);
	print_keyboard(tester, line);
	tester->c = getchar();
	tester->start_time = get_time_ms();
	while (tester->c != ESC)
	{
		tester->is_correct = -1;
		if (tester->c == ' ')
		{
			if (cur_word->pos != 0)
			{
				tester->inputs_count++;
				check_input(tester, tester->c, cur_word);
				if (cur_word->next == NULL)
					break ;
				tester->cur_word_idx++;
				cur_word = cur_word->next;
			}
		}
		else if (ft_isprint(tester->c) && cur_word->pos < BUFSIZE - 1)
		{
			cur_word->input_buf[cur_word->pos] = tester->c;
			check_input(tester, tester->c, cur_word);
			cur_word->pos++;
			tester->inputs_count++;
		}
		else if (tester->c == BACKSPACE)
		{
			if (cur_word->pos > 0)
			{
				cur_word->input_buf[cur_word->pos] = 0;
				cur_word->pos--;
			}
			else
			{
				if (cur_word->prev != NULL)
				{
					cur_word = cur_word->prev;
					tester->cur_word_idx--;
				}
			}
		}
		line = print_wordlist(tester);
		print_keyboard(tester, line);
		if (tester->cur_word_idx == tester->num_words - 1 && ft_strcmp(cur_word->input_buf, cur_word->word) == 0)
			break ;
		tester->c = getchar();
	}
	tester->end_time = get_time_ms();
}

void	game_loop(t_typer *tester)
{
	int	retval;

	do {
		run_game(tester);
		retval = display_stats(tester);
		clear_wordlist(&tester->wordlist);
	} while (retval == 0);
}
