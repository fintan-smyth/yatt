/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:15:30 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/02 00:48:55 by fsmyth           ###   ########.fr       */
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

	tester->c = 0;
	draw_borders(tester);
	print_keyboard_picker(tester, tester->env->win_height / 2 - 6);
	tester->c = getchar();
	while (tester->c != ESC)
	{
		print_keyboard_picker(tester, tester->env->win_height / 2 - 6);
		if (ft_isalpha(tester->c) || tester->c == ' ')
		{
			c = getchar();
			if (c >= '0' && c <= '7')
				tester->fingers[tester->c] = c - '0';
			tester->c = 0;
			print_keyboard_picker(tester, tester->env->win_height / 2 - 6);
		}
		tester->c = getchar();
	}
}
