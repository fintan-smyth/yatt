/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:50:15 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/03 23:25:22 by fsmyth           ###   ########.fr       */
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
	term.c_cc[VMIN] = 1;
	tcsetattr(fileno(stdin), TCSANOW, &term);
	ft_printf("\e[?25l");
	ft_printf("\e[?1049h");
}

void	reset_term_settings(t_env *env)
// Restores terminal attributes to their original state
{
	struct termios term;
	term = env->g_term_original;
	tcsetattr(fileno(stdin), TCSANOW, &term);
	ft_printf("\e[?1049l");
	ft_printf("\e[?25h");
}

int	set_winsize(t_env *env)
// Sets global variables containing terminal dimensions
{
	struct winsize w;
	int	old_width = env->win_width;
	int	old_height = env->win_height;

	ioctl(0, TIOCGWINSZ, &w);
	env->win_width = w.ws_col;
	env->win_height = w.ws_row;
	if (env->win_width != old_width || env->win_height != old_height)
		return (1);
	return (0);
}
