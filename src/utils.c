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

void	draw_borders(t_typer *tester)
{
	int	i;

	ft_printf("\e[2J\e[H╭");
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("╮", 1);
	i = 1;
	while (i++ < tester->env->win_height - 1)
		ft_printf("\e[%d;H│\e[\e[%dG│", i, tester->env->win_width);
	ft_putstr_fd("╰", 1);
	i = 2;
	while (i++ < tester->env->win_width)
		ft_putstr_fd("─", 1);
	ft_putstr_fd("╯", 1);
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
		right = set[0];
	len = ft_strlen(str);
	ft_memmove(str + 1, str, len);
	str[0] = left;
	str[len + 1] = right;
	str[len + 2] = 0;
}

int	clamp_int(int num, int min, int max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
