/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:15:30 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/01 23:51:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

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
