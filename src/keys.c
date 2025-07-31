/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:02:18 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/03 00:52:30 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <ncurses.h>

void	print_formatted_key(t_typer *tester, char c, t_word *cur_word)
{
	attron(COLOR_PAIR(DEFAULT_COLS));
	if (tester->options.kmode == 0)
	{
		if (c == tester->c)
		{
			if (tester->is_correct)
				attron(COLOR_PAIR(GREEN_BG));
			else
				attron(COLOR_PAIR(RED_BG));
		}
		printw(" %c ", ft_toupper(c));
	}
	else if (tester->options.kmode == 1)
	{
		int	pos = cur_word->pos;
		int	len = cur_word->len;
		int	col = tester->options.fingers[(unsigned char)c];

		if (pos < len && c == cur_word->word[pos])
			col += 8;
		attron(COLOR_PAIR(col));
		printw(" %c ", ft_toupper(c));
	}
	attron(COLOR_PAIR(DEFAULT_COLS));
	add_wch(&tester->boxchars[0]);
}

void	print_formatted_space(t_typer *tester, t_word *cur_word)
{
	char	space[] = "     SPACE     ";

	if (tester->options.kmode == 0)
	{
		if (' ' == tester->c && tester->is_correct >= 0)
		{
			if (tester->is_correct)
				ft_printf("│\e[30;42m%s\e[39;49m│", space);
			else
				ft_printf("│\e[30;41m%s\e[39;49m│", space);
		}
		else
			ft_printf("│%s│", space);
	}
	else if (tester->options.kmode == 1)
	{
		int	pos = cur_word->pos;
		int	len = cur_word->len;

		if (pos == len)
			ft_printf("│\e[30;4%dm%s\e[39;49m│", tester->options.fingers[' '], space);
		else
			ft_printf("│\e[3%dm%s\e[39;49m│", tester->options.fingers[' '], space);
	}
}

void	print_formatted_wordkey(t_typer *tester, t_word *cur_word, unsigned char key);

int print_keyboard(t_typer *tester, int y, t_word *cur_word)
{
	char	row1[] = "qwertyuiop";
	char	row2[] = "asdfghjkl";
	char	row3[] = "zxcvbnm";
	int		i;
	int		line_start;

	line_start = (tester->env->win_width - 41) / 2;
	y += 2;
	attrset(A_BOLD);
	mvaddwstr(y++, line_start, L"┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = -1;
	while (row1[++i])
		print_formatted_key(tester, row1[i], cur_word);
	mvaddwstr(y++, line_start++, L"└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = -1;
	while (row2[++i])
		print_formatted_key(tester, row2[i], cur_word);
	mvaddwstr(y++, line_start++, L"└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┘");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = -1;
	while (row3[++i])
		print_formatted_key(tester, row3[i], cur_word);
	mvaddwstr(y++, line_start, L"└───┴───┴┬──┴───┴───┴───┴┬──┘");
	line_start += 9;
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
		print_formatted_wordkey(tester, cur_word, ' ');
	mvaddwstr(y++, line_start, L"└───────────────┘");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	return (y);
}

void	print_formatted_key_non_alpha(t_typer *tester, char *keyset, int i, t_word *cur_word)
{
	const char	c = keyset[i];
	const char	c_alt = keyset[i + 1];
	const char	input = tester->c;
	char		display_c;

	attron(COLOR_PAIR(DEFAULT_COLS));
	if (tester->options.kmode == 0)
	{
		display_c = (c_alt == input ? c_alt : c);

		if (c == input || c_alt == input)
		{
			if (tester->is_correct)
				attron(COLOR_PAIR(GREEN_BG));
			else
				attron(COLOR_PAIR(RED_BG));
		}
		printw(" %c ", display_c);
	}
	else if (tester->options.kmode == 1)
	{
		int		pos = cur_word->pos;
		int		len = cur_word->len;
		char	next = cur_word->word[pos];
		int		col = 0;

		display_c = c;
		if (pos < len && (c == next || c_alt == next))
		{
			display_c = next;
			col = 8;
			// ft_printf("\e[30;4%dm %c \e[39;49m", tester->options.fingers[(unsigned char)next], next);
		}
		// else
			// ft_printf("\e[3%dm %c \e[39;49m", tester->options.fingers[(unsigned char)c], c);
		col += tester->options.fingers[(unsigned char)display_c];
		attron(COLOR_PAIR(col));
		printw(" %c ", display_c);
	}
	attron(COLOR_PAIR(DEFAULT_COLS));
	if (c == '\\')
		addch(' ');
	add_wch(&tester->boxchars[0]);
	// ft_printf("%s│", c == '\\' ? " " : "");
}

void	print_formatted_wordkey(t_typer *tester, t_word *cur_word, unsigned char key)
{
	char	enter[] = "  Enter  ";
	char	backspace[] = "  <--  ";
	char	space[] = "     SPACE     ";
	char	space_big[] = "        SPACE        ";
	char	*wordkey;

	if (key == '\n')
		wordkey = enter;
	else if (key == BACKSPACE)
		wordkey = backspace;
	else if (key == ' ')
	{
		if (tester->options.full_keyboard)
			wordkey = space_big;
		else
			wordkey = space;
	}
	if (tester->options.kmode == 0)
	{
		if (key == tester->c && tester->is_correct >= 0)
		{
			if (tester->is_correct)
			{
				// ft_printf("\e[30;42m%s\e[39;49m│", wordkey);
				attron(COLOR_PAIR(GREEN_BG));
				printw("%s", wordkey);
			}
			else
			{
				// ft_printf("\e[30;41m%s\e[39;49m│", wordkey);
				attron(COLOR_PAIR(RED_BG));
				printw("%s", wordkey);
			}
		}
		else
		// ft_printf("%s│", wordkey);
			printw("%s", wordkey);
	}
	else if (tester->options.kmode == 1)
	{
		int	pos = cur_word->pos;
		int	len = cur_word->len;
		int	col = tester->options.fingers[key];

		if ((key == ' ' && pos == len) || (key == BACKSPACE && !tester->is_correct))
			col += 8;
		attron(COLOR_PAIR(col));
		printw("%s", wordkey);
	}
	attron(COLOR_PAIR(DEFAULT_COLS));
	add_wch(&tester->boxchars[0]);
}

int print_keyboard_full(t_typer *tester, int y, t_word *cur_word)
{
	char	row0[] = "1!2@3#4$5%6^7&8*9(0)-_=+";
	char	row1[] = "qwertyuiop[{]}";
	char	row2[] = "asdfghjkl;:'\"";
	char	row3[] = "zxcvbnm,<.>/?";
	int		i;
	int		line_start;

	line_start = (tester->env->win_width - 51) / 2;
	y += 2;
	// ft_printf("\e[1m\e[%d;%dH┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐", y++, line_start);
	// ft_printf("\e[%d;%dH│", y++, line_start);
	attrset(A_BOLD);
	mvaddwstr(y++, line_start, L"┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = 0;
	while (row0[i])
	{
		print_formatted_key_non_alpha(tester, row0, i, cur_word);
		i += 2;
	}
	// ft_printf("\e[1m\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐", y++, line_start++);
	// ft_printf("\e[%d;%dH│", y++, line_start);
	mvaddwstr(y++, line_start++, L"└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = 0;
	while (row1[i])
	{
		if (ft_isalpha(row1[i]))
		{
			print_formatted_key(tester, row1[i], cur_word);
			i++;
		}
		else
		{
			print_formatted_key_non_alpha(tester, row1, i, cur_word);
			i += 2;
		}
	}
	// ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘", y++, line_start++);
	// ft_printf("\e[%d;%dH│", y++, line_start);
	mvaddwstr(y++, line_start++, L"└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = 0;
	while (row2[i])
	{
		if (ft_isalpha(row2[i]))
		{
			print_formatted_key(tester, row2[i], cur_word);
			i++;
		}
		else
		{
			print_formatted_key_non_alpha(tester, row2, i, cur_word);
			i += 2;
		}
	}
	// ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘", y++, line_start++);
	// ft_printf("\e[%d;%dH│", y++, line_start);
	mvaddwstr(y++, line_start++, L"└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘");
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	i = 0;
	while (row3[i])
	{
		if (ft_isalpha(row3[i]))
		{
			print_formatted_key(tester, row3[i], cur_word);
			i++;
		}
		else
		{
			print_formatted_key_non_alpha(tester, row3, i, cur_word);
			i += 2;
		}
	}
	// ft_printf("\e[%d;%dH└───┴───┴┬──┴───┴───┴───┴───┴──┬┴───┴───┘", y++, line_start);
	// line_start += 9;
	// ft_printf("\e[%d;%dH│", y++, line_start);
	mvaddwstr(y++, line_start, L"└───┴───┴┬──┴───┴───┴───┴───┴──┬┴───┴───┘");
	line_start += 9;
	mvadd_wch(y++, line_start, &tester->boxchars[0]);
	// print_formatted_space(tester, cur_word);
	print_formatted_wordkey(tester, cur_word, ' ');
	// ft_printf("\e[%d;%dH└─────────────────────┘", y++, line_start);
	mvaddwstr(y++, line_start, L"└─────────────────────┘");
	attrset(A_NORMAL | COLOR_PAIR(DEFAULT_COLS));
	return (y);
}

void	print_picker_key(t_typer *tester, unsigned char c)
{
	char	space[] = "     SPACE     ";

	if (c != ' ')
	{
		if (tester->c == c)
			ft_printf("\e[30;47m %c \e[39;49m", ft_toupper(c));
		else
			ft_printf("\e[3%dm %c \e[39;49m", tester->options.fingers[c], ft_toupper(c));
		ft_putstr_fd("│", 1);
	}
	else
	{
		if (tester->c == c)
			ft_printf("│\e[30;47m%s\e[39;49m│", space);
		else
			ft_printf("│\e[3%dm%s\e[39;49m│", tester->options.fingers[' '], space);
	}
}

int	print_col_hints(t_typer *tester, int y)
{
	char	line1[] = "\e[1;30mBLACK:\e[39m   0        \e[34mBLUE:\e[39m     4";
	char	line2[] = "\e[1;31mRED:\e[39m     1        \e[35mMAGENTA:\e[39m  5";
	char	line3[] = "\e[1;32mGREEN:\e[39m   2        \e[36mCYAN:\e[39m     6";
	char	line4[] = "\e[1;33mYELLOW:\e[39m  3        \e[37mWHITE:\e[39m    7";

	print_str_centred(line1, y++, tester->env->win_width);
	print_str_centred(line2, y++, tester->env->win_width);
	print_str_centred(line3, y++, tester->env->win_width);
	print_str_centred(line4, y++, tester->env->win_width);
	return (y);
}

void	print_keyboard_picker(t_typer *tester)
{
	char	row1[] = "qwertyuiop";
	char	row2[] = "asdfghjkl";
	char	row3[] = "zxcvbnm";
	int		i;
	int		y;
	int		line_start;

	draw_borders(tester);
	y= tester->env->win_height / 2 - 6;
	y = print_col_hints(tester, y);
	line_start = (tester->env->win_width - 41) / 2 + 1;
	y += 2;
	ft_printf("\e[1m\e[%d;%dH┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐", y++, line_start);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row1[++i])
		print_picker_key(tester, row1[i]);
	ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘", y++, line_start++);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row2[++i])
		print_picker_key(tester, row2[i]);
	ft_printf("\e[%d;%dH└┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┘", y++, line_start++);
	ft_printf("\e[%d;%dH│", y++, line_start);
	i = -1;
	while (row3[++i])
		print_picker_key(tester, row3[i]);
	ft_printf("\e[%d;%dH└───┴───┴┬──┴───┴───┴───┴┬──┘", y++, line_start);
	line_start += 9;
	ft_printf("\e[%d;%dH", y++, line_start);
	print_picker_key(tester, ' ');
	ft_printf("\e[%d;%dH└───────────────┘", y++, line_start);
	ft_printf("\e[m\n");
}
