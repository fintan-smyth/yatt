/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:15:30 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/02 01:11:35 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <stdio.h>

void	set_key_col(t_typer *tester, unsigned char c, int col)
{
	if (col < 0 || col > 7)
		return ;
	tester->fingers[c] = col;
	tester->fingers[ft_toupper(c)] = col;
}

void	set_keyset_col(t_typer *tester, char *keyset, int col)
{
	int	i;

	i = -1;
	while (keyset[++i])
		set_key_col(tester, keyset[i], col);
}

void	setup_default_fingers(t_typer *tester)
{
	char			index_l[] = "rtfgcvb";
	char			middle_l[] = "edx";
	char			ring_l[] = "wsz";
	char			pinky_l[] = "qa";

	char			index_r[] = "yhnujm";
	char			middle_r[] = "ik";
	char			ring_r[] = "ol";
	char			pinky_r[] = "p";

	char			thumb[] = " ";

	set_keyset_col(tester, index_l, BLUE);
	set_keyset_col(tester, index_r, MAGENTA);
	set_keyset_col(tester, middle_l, RED);
	set_keyset_col(tester, middle_r, RED);
	set_keyset_col(tester, ring_l, GREEN);
	set_keyset_col(tester, ring_r, GREEN);
	set_keyset_col(tester, pinky_l, YELLOW);
	set_keyset_col(tester, pinky_r, YELLOW);
	set_keyset_col(tester, thumb, CYAN);
}

void	pick_key_cols(t_typer *tester)
{
	char	c;
	int		y_start;

	y_start = tester->env->win_height / 2 - 6;
	tester->c = 0;
	draw_borders(tester);
	print_keyboard_picker(tester, y_start);
	tester->c = getchar();
	while (tester->c != ESC)
	{
		print_keyboard_picker(tester, y_start);
		if (ft_isalpha(tester->c) || tester->c == ' ')
		{
			c = getchar();
			if (c >= '0' && c <= '7')
				tester->fingers[tester->c] = c - '0';
			tester->c = 0;
			print_keyboard_picker(tester, y_start);
		}
		tester->c = getchar();
	}
}

void	print_menu_screen(t_typer *tester)
{
	int		line;
	int		width = ft_strlen(tester->lang.name) + 5;
	char	buf1[128];
	char	buf2[128];

	draw_borders(tester);
	line = tester->env->win_height / 2 - 2;
	snprintf(buf1, 128, "\e[1;34m<%*s\e[m", width, ">");
	if (tester->menu_state.selected == 0)
		print_str_centred(buf1, line, tester->env->win_width);
	snprintf(buf2, 128, "\e[1m%d\e[m", tester->num_words);
	print_str_centred(buf2, line, tester->env->win_width);
	line += 2;
	if (tester->menu_state.selected == 1)
		print_str_centred(buf1, line, tester->env->win_width);
	snprintf(buf2, 128, "\e[1m%s\e[m", tester->lang.name);
	print_str_centred(buf2, line, tester->env->win_width);
	line += 2;
	if (tester->menu_state.selected == 2)
		print_str_centred("\e[30;44;1mChoose key colours\e[m", line, tester->env->win_width);
	else
		print_str_centred("\e[1mChoose key colours\e[m", line, tester->env->win_width);
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

void	render_options(t_typer *tester)
{
	char	c;

	print_menu_screen(tester);
	c = getchar();
	while (c != 'q')
	{
		if (c == 'j')
			change_selection(&tester->menu_state, 1);
		else if (c == 'k')
			change_selection(&tester->menu_state, -1);
		print_menu_screen(tester);
		c = getchar();
	}
}
