/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:50:15 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/26 20:01:50 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"
#include <termios.h>

void	store_term_settings(t_typer *tester)
// Stores the original terminal emulator attributes
{
	tcgetattr(STDIN_FILENO, &tester->g_term_original);
}

void	set_term_settings(t_typer *tester)
// Sets the terminal attributes to those
// needed by the program:
//  - Disabling STDIN echo
//  - Processing single characters from STDIN as they appear
//  - Turning off cursor
{
	struct termios term;

	term = tester->g_term_original;
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~(ICANON);
	tcsetattr(fileno(stdin), TCSANOW, &term);
	printf("\e[?25l");
}

void	reset_term_settings(t_typer *tester)
// Restores terminal attributes to their original state
{
	struct termios term;
	term = tester->g_term_original;
	tcsetattr(fileno(stdin), TCSANOW, &term);
	printf("\e[?25h");
}
