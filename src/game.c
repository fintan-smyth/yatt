/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:39:56 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/04 00:05:36 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

void	reset_game(t_typer *tester)
{
	select_words(tester);
	tester->inputs_count = 0;
	tester->cur_word_idx = 0;
	tester->incorrect_inputs = 0;
	tester->c = 0;
}

void	render_game(t_typer *tester)
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
	if (tester->options.full_keyboard)
		print_keyboard_full(tester, line, tester->cur_word);
	else
		print_keyboard(tester, line, tester->cur_word);
}

void	run_game(t_typer *tester)
{
	reset_game(tester);
	tester->cur_word = tester->wordlist;
	render_game(tester);
	tester->c = getchar_nb(tester, render_game);
	tester->start_time = get_time_ms();
	while (tester->c != ESC)
	{
		tester->is_correct = 1;
		if (tester->c == ' ')
		{
			if (tester->cur_word->pos != 0)
			{
				tester->inputs_count++;
				check_input(tester, tester->c, tester->cur_word);
				if (tester->cur_word->next == NULL)
					break ;
				tester->cur_word_idx++;
				tester->cur_word = tester->cur_word->next;
			}
		}
		else if (ft_isprint(tester->c) && tester->cur_word->pos < tester->env->win_width - 6 && tester->cur_word->pos < BUFSIZE)
		{
			tester->cur_word->input_buf[tester->cur_word->pos] = tester->c;
			check_input(tester, tester->c, tester->cur_word);
			tester->cur_word->pos++;
			tester->inputs_count++;
		}
		else if (tester->c == BACKSPACE)
		{
			if (tester->cur_word->pos > 0)
			{
				tester->cur_word->pos--;
				tester->cur_word->input_buf[tester->cur_word->pos] = 0;
			}
			else
			{
				if (tester->cur_word->prev != NULL)
				{
					tester->cur_word = tester->cur_word->prev;
					tester->cur_word_idx--;
				}
			}
		}
		else
		{
			tester->c = getchar_nb(tester, render_game);
			continue ;
		}
		render_game(tester);
		if (tester->cur_word_idx == tester->options.num_words - 1
			&& ft_strcmp(tester->cur_word->input_buf, tester->cur_word->word) == 0)
			break ;
		tester->c = getchar_nb(tester, render_game);
	}
	tester->end_time = get_time_ms();
}

void	game_loop(t_typer *tester)
{
	int	retval;

	do {
		run_game(tester);
		retval = stats_screen(tester);
		clear_wordlist(&tester->wordlist);
	} while (retval != 1);
}
