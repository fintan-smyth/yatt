/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:44:19 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/03 23:54:27 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

size_t	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_output_len(char *str)
{
	int	len;
	int	in_escape;

	len = 0;
	in_escape = 0;
	while (*str)
	{
		if (*str == '\e')
			in_escape = 1;
		else if (in_escape == 1)
		{
			if (ft_isalpha(*str))
				in_escape = 0;
		}
		else
			len++;
		str++;
	}
	return (len);
}

int	print_str_centred(char *str, int row, int width)
{
	int	start_x;
	int	len;

	len = ft_output_len(str);
	start_x = (width - len) / 2 + 1;
	ft_printf("\e[%d;%dH%s", row, start_x, str);
	return (start_x);
}

void	centre_str(char *str, int row, int width)
{
	int	start_x;
	int	len;

	len = ft_output_len(str);
	start_x = (width - len) / 2;
	move(row, start_x);
}

void	draw_borders(t_typer *tester)
{
	cchar_t	*boxchars = tester->boxchars;

	border_set(
		&boxchars[0],
		&boxchars[0],
		&boxchars[1],
		&boxchars[1],
		&boxchars[2],
		&boxchars[3],
		&boxchars[4],
		&boxchars[5]
	);
}

int	kbhit(void)
{
	struct timeval	tv;
	fd_set			fds;

	tv.tv_sec = 0;
	tv.tv_usec = POLL_US;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(1, &fds, NULL, NULL, &tv);
	return (FD_ISSET(STDIN_FILENO, &fds));
}

int	get_escape_char(char *sequence)
{
	if (sequence[1] == 0)
		return (ESC);
	if (sequence[1] == 91)
	{
		char	dir = sequence[2];
		if (dir == 65)
			return (K_UP);
		if (dir == 66)
			return (K_DOWN);
		if (dir == 67)
			return (K_RIGHT);
		if (dir == 68)
			return (K_LEFT);
	}
	return (-1);
}

void	render_too_small(t_typer *tester)
{
	int		y = tester->env->win_height / 2;

	draw_borders(tester);
	print_str_centred("\e[1;3mWindow too small!", y, tester->env->win_width);
}

int	win_too_small(t_env *env)
{
	return (env->win_height < env->min_height || env->win_width < env->min_width);
}

void	exec_render_func(t_typer *tester, void (*render)(t_typer *))
{
	if (win_too_small(tester->env))
	{
		render_too_small(tester);
		return ;
	}
	render(tester);
}

char	getchar_nb(t_typer *tester, void (*render)(t_typer *))
{
	char	c[4] = {};
	t_env	*env = tester->env;

	// refresh();
	while (!kbhit())
	{
		if (set_winsize(env))
			exec_render_func(tester, render);
	}
	read(0, c, 3);
	if (c[0] == ESC)
		return (get_escape_char(c));
	return (c[0]);
}

void	surround_string(char *str, char *set)
{
	char	left;
	char	right;
	int		len;

	len = ft_strlen(set);
	if (len > 2)
		return ;
	left = set[0];
	if (len == 2)
		right = set[1];
	else
		right = '\0';
	len = ft_strlen(str);
	ft_memmove(str + 1, str, len);
	str[0] = left;
	str[len + 1] = right;
	str[len + 2] = 0;
}

void	prefix_string(char *str, char *prefix)
{
	int	str_len;
	int	prefix_len;

	str_len = ft_strlen(str);
	prefix_len = ft_strlen(prefix);
	ft_memmove(str + prefix_len, str, str_len + 1);
	ft_memmove(str, prefix, prefix_len);
}

int	clamp_int(int num, int min, int max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

int	pos_mod(int num, int mod)
{
	return ((num % mod + mod) % mod);
}
