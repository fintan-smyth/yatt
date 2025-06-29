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
#include <sys/ioctl.h>
#include <sys/stat.h>

void	store_term_settings(t_env *env)
// Stores the original terminal emulator attributes
{
	tcgetattr(STDIN_FILENO, &env->g_term_original);
}

void	set_term_settings(t_env *env)
// Sets the terminal attributes to those
// needed by the program:
//  - Disabling STDIN echo
//  - Processing single characters from STDIN as they appear
//  - Turning off cursor
{
	struct termios term;

	term = env->g_term_original;
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~(ICANON);
	tcsetattr(fileno(stdin), TCSANOW, &term);
	printf("\e[?25l");
}

void	reset_term_settings(t_env *env)
// Restores terminal attributes to their original state
{
	struct termios term;
	term = env->g_term_original;
	tcsetattr(fileno(stdin), TCSANOW, &term);
	printf("\e[?25h");
}

void	set_winsize(t_env *env)
// Sets global variables containing terminal dimensions
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	env->win_width = w.ws_col;
	env->win_height = w.ws_row;
}
