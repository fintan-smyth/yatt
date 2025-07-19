/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:15:30 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/14 00:24:58 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <stdio.h>

void	set_key_col(t_options *options, unsigned char c, int col)
{
	if (col < 0 || col > 7)
		return ;
	options->fingers[c] = col;
	options->fingers[ft_toupper(c)] = col;
}

void	set_keyset_col(t_options *options, char *keyset, int col)
{
	int	i;

	i = -1;
	while (keyset[++i])
		set_key_col(options, keyset[i], col);
}

void	setup_default_fingers(t_options *options)
{
	char	index_l[]	= "rtfgcvb4$5%";
	char	middle_l[]	= "edx3#";
	char	ring_l[]	= "wsz2@";
	char	pinky_l[]	= "qa1!";

	char	index_r[]	= "yhnujm6^7&";
	char	middle_r[]	= "ik,<8*";
	char	ring_r[]	= "ol.>9(";
	char	pinky_r[]	= "p0);:/?'\"[{]}-_=+";

	char	thumb[]		= " ";

	for (int i = 0; i < 128; i++)
		options->fingers[i] = 7;
	set_keyset_col(options, index_l, BLUE);
	set_keyset_col(options, index_r, MAGENTA);
	set_keyset_col(options, middle_l, RED);
	set_keyset_col(options, middle_r, RED);
	set_keyset_col(options, ring_l, GREEN);
	set_keyset_col(options, ring_r, GREEN);
	set_keyset_col(options, pinky_l, YELLOW);
	set_keyset_col(options, pinky_r, YELLOW);
	set_keyset_col(options, thumb, CYAN);
}

void	pick_key_cols(t_typer *tester)
{
	char	c;

	tester->c = 0;
	exec_render_func(tester, print_keyboard_picker);
	tester->c = getchar_nb(tester, print_keyboard_picker);
	while (tester->c != ESC)
	{
		exec_render_func(tester, print_keyboard_picker);
		if (ft_isalpha(tester->c) || tester->c == ' ')
		{
			c = getchar_nb(tester, print_keyboard_picker);
			if (c >= '0' && c <= '7')
				tester->options.fingers[tester->c] = c - '0';
			tester->c = 0;
			exec_render_func(tester, print_keyboard_picker);
		}
		tester->c = getchar_nb(tester, print_keyboard_picker);
	}
}

void	print_menu_words(t_typer *tester, int selected, int line)
{
	char	buf[128];

	print_str_centred("\e[1;34mNo. Words:\e[m", line, tester->env->win_width * 2 / 3);
	ft_snprintf(buf, 128, "\e[31m%s\e[m  %d  \e[31m%s\e[m",
		(selected && tester->options.num_words > 1) ? "<" : " ",
		tester->options.num_words,
		(selected && tester->options.num_words < 250) ? ">" : " ");
	print_str_centred(buf, line, tester->env->win_width * 4 / 3);
}

void	print_menu_numbers(t_typer *tester, int selected, int line)
{
	char	buf[128];

	print_str_centred("\e[1;36mNumbers:\e[m", line, tester->env->win_width * 2 / 3);
	ft_snprintf(buf, 128, "\e[31m%s\e[m  %s  \e[31m%s\e[m",
		selected ? "<" : " ",
		tester->options.numbers ? "On" : "Off",
		selected ? ">" : " ");
	print_str_centred(buf, line, tester->env->win_width * 4 / 3);
}

void	print_menu_punc(t_typer *tester, int selected, int line)
{
	char	buf[128];
	char	*strs[3] = {"Off", "Standard", "C-style"};

	print_str_centred("\e[1;36mPunctuation:\e[m", line, tester->env->win_width * 2 / 3);
	ft_snprintf(buf, 128, "\e[31m%s\e[m  %s  \e[31m%s\e[m",
		selected ? "<" : " ",
		strs[tester->options.punc],
		selected ? ">" : " ");
	print_str_centred(buf, line, tester->env->win_width * 4 / 3);
}

void	print_menu_lang(t_typer *tester, int selected, int line)
{
	char	buf[128];

	print_str_centred("\e[1;32mLanguage:\e[m", line, tester->env->win_width * 2 / 3);
	ft_snprintf(buf, 128, "\e[31m%s\e[m  %s  \e[31m%s\e[m",
		selected ? "<" : " ",
		extract_lang_name(tester->options.cur_lang->str),
		selected ? ">" : " ");
	print_str_centred(buf, line, tester->env->win_width * 4 / 3);
}

void	print_menu_kmode(t_typer *tester, int selected, int line)
{
	char	buf[128];

	print_str_centred("\e[1;33mKeyboard mode:\e[m", line, tester->env->win_width * 2 / 3);
	ft_snprintf(buf, 128, "\e[31m%s\e[m  %s  \e[31m%s\e[m",
		selected ? "<" : " ",
		tester->options.kmode ? "Instructional" : "Accuracy",
		selected ? ">" : " ");
	print_str_centred(buf, line, tester->env->win_width * 4 / 3);
}

void	print_menu_screen(t_typer *tester)
{
	int		line;

	draw_borders(tester);
	line = tester->env->win_height / 2 - 4;
	print_menu_words(tester, tester->menu_state.selected == M_WORDS, line);
	line += 2;
	print_menu_numbers(tester, tester->menu_state.selected == M_NUMBERS, line);
	line += 2;
	print_menu_punc(tester, tester->menu_state.selected == M_PUNC, line);
	line += 2;
	print_menu_lang(tester, tester->menu_state.selected == M_LANG, line);
	line += 2;
	print_menu_kmode(tester, tester->menu_state.selected == M_KMODE, line);
	line += 3;
	if (tester->menu_state.selected == M_KEYCOLS)
		print_str_centred("\e[30;45;1mChoose key colours\e[m", line, tester->env->win_width);
	else
		print_str_centred("\e[35;1mChoose key colours\e[m", line, tester->env->win_width);
}

void	change_selection(t_menu *menu, int dir)
{
	int	selected;

	if (dir != 1 && dir != -1)
		return ;
	selected = menu->selected;
	selected += dir;
	if (selected == menu->no_entries)
		selected = 0;
	if (selected < 0)
		selected = menu->no_entries - 1;
	menu->selected = selected;
}

void	menu_change_value(t_typer *tester, int dir)
{
	int			selected;
	t_options	*options = &tester->options;

	if (dir != 1 && dir != -1)
		return ;
	selected = tester->menu_state.selected;
	if (selected == M_WORDS)
	{
		int	new_val = clamp_int(options->num_words + dir, 1, 250);

		options->num_words = new_val;
		return ;
	}
	if (selected == M_LANG)
	{
		if (dir == 1)
		{
			options->cur_lang = options->cur_lang->next;
			if (options->cur_lang == NULL)
				options->cur_lang = options->lang_paths;
			return ;
		}
		if (options->cur_lang == options->lang_paths)
		{
			options->cur_lang = ft_lstlast(options->lang_paths);
			return ;
		}
		t_list	*current = options->lang_paths;
		
		while (current->next != options->cur_lang)
			current = current->next;
		options->cur_lang = current;
		return ;
	}
	if (selected == M_KMODE)
		tester->options.kmode = !tester->options.kmode;
	if (selected == M_PUNC)
		tester->options.punc = pos_mod(tester->options.punc + dir, PMODE_MAX);
	if (selected == M_NUMBERS)
		tester->options.numbers = !tester->options.numbers;
}

void	render_options(t_typer *tester)
{
	char	c;

	tester->menu_state.selected = 0;
	exec_render_func(tester, print_menu_screen);
	c = getchar_nb(tester, print_menu_screen);
	while (c != 'q' && c != ESC)
	{
		if (c == 'j' || c == K_DOWN)
			change_selection(&tester->menu_state, 1);
		else if (c == 'k' || c == K_UP)
			change_selection(&tester->menu_state, -1);
		else if (c == 'h' || c == K_LEFT)
			menu_change_value(tester, -1);
		else if (c == 'l' || c == K_RIGHT)
			menu_change_value(tester, 1);
		else if ((c == ' ' || c == '\n') && tester->menu_state.selected == M_KEYCOLS)
			pick_key_cols(tester);
		exec_render_func(tester, print_menu_screen);
		c = getchar_nb(tester, print_menu_screen);
	}
	if (ft_strcmp(extract_lang_name(tester->options.cur_lang->str), tester->lang.name) != 0)
	{
		cleanup_lang(&tester->lang);
		tester->lang = load_language_file(tester->options.cur_lang->str);
	}
	if (tester->options.punc || tester->options.numbers)
	{
		tester->options.full_keyboard = 1;
		tester->env->min_height = MIN_HEIGHT_FULL;
		tester->env->min_width = MIN_WIDTH_FULL;
	}
	else
	{
		tester->options.full_keyboard = 0;
		tester->env->min_height = MIN_HEIGHT_SMALL;
		tester->env->min_width = MIN_WIDTH_SMALL;
	}
}
