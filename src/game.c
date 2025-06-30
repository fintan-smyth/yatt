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

int	render_game(t_typer *tester, int finished)
{
	int	line;
	int	i;

	ft_printf("\e[2J\e[H╭");
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("╮", 1);
	ft_printf("\e[2;H│\e[\e[%dG│", i, tester->env->win_width);
	line = print_wordlist(tester);
	ft_printf("\e[%d;1H├", line);
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("┤", 1);
	i = line;
	while (i++ < tester->env->win_height - 1)
		ft_printf("\e[%d;H│\e[\e[%dG│", i, tester->env->win_width);
	ft_putstr_fd("╰", 1);
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("╯", 1);
	if (finished)
		return (display_stats(tester, line));
	line = print_keyboard(tester, line);
	// char	buf[1024];
	// ft_snprintf(buf, 1024, "\e[33;1mCorrect inputs\e[m: %d/%d", tester->inputs_count - tester->incorrect_inputs, tester->inputs_count);
	// print_str_centred(buf, ++line, tester->env->win_width);
	return (line);
}

int	run_game(t_typer *tester)
{
	t_word	*cur_word;

	reset_game(tester);
	cur_word = tester->wordlist;
	render_game(tester, 0);
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
		else if (ft_isprint(tester->c) && cur_word->pos < tester->env->win_width - 6)
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
				cur_word->pos--;
				cur_word->input_buf[cur_word->pos] = 0;
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
		render_game(tester, 0);
		if (tester->cur_word_idx == tester->num_words - 1 && ft_strcmp(cur_word->input_buf, cur_word->word) == 0)
			break ;
		tester->c = getchar();
	}
	tester->end_time = get_time_ms();
	return (render_game(tester, 1));
}

void	game_loop(t_typer *tester)
{
	int	retval;

	do {
		retval = run_game(tester);
		clear_wordlist(&tester->wordlist);
	} while (retval == 0);
}
