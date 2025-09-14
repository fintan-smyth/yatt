/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphtest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:23:13 by fsmyth            #+#    #+#             */
/*   Updated: 2025/09/14 20:34:30 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"
#include <fcntl.h>
#include <math.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void	set_graphcars(t_typer *tester)
{
	setcchar(&tester->graphchars[0], L" ", 0, 0, NULL);
	setcchar(&tester->graphchars[1], L"⢀", 0, 0, NULL);
	setcchar(&tester->graphchars[2], L"⢠", 0, 0, NULL);
	setcchar(&tester->graphchars[3], L"⢰", 0, 0, NULL);
	setcchar(&tester->graphchars[4], L"⢸", 0, 0, NULL);
	setcchar(&tester->graphchars[5], L"⡀", 0, 0, NULL);
	setcchar(&tester->graphchars[6], L"⣀", 0, 0, NULL);
	setcchar(&tester->graphchars[7], L"⣠", 0, 0, NULL);
	setcchar(&tester->graphchars[8], L"⣰", 0, 0, NULL);
	setcchar(&tester->graphchars[9], L"⣸", 0, 0, NULL);
	setcchar(&tester->graphchars[10], L"⡄", 0, 0, NULL);
	setcchar(&tester->graphchars[11], L"⣄", 0, 0, NULL);
	setcchar(&tester->graphchars[12], L"⣤", 0, 0, NULL);
	setcchar(&tester->graphchars[13], L"⣴", 0, 0, NULL);
	setcchar(&tester->graphchars[14], L"⣼", 0, 0, NULL);
	setcchar(&tester->graphchars[15], L"⡆", 0, 0, NULL);
	setcchar(&tester->graphchars[16], L"⣆", 0, 0, NULL);
	setcchar(&tester->graphchars[17], L"⣦", 0, 0, NULL);
	setcchar(&tester->graphchars[18], L"⣶", 0, 0, NULL);
	setcchar(&tester->graphchars[19], L"⣾", 0, 0, NULL);
	setcchar(&tester->graphchars[20], L"⡇", 0, 0, NULL);
	setcchar(&tester->graphchars[21], L"⣇", 0, 0, NULL);
	setcchar(&tester->graphchars[22], L"⣧", 0, 0, NULL);
	setcchar(&tester->graphchars[23], L"⣷", 0, 0, NULL);
	setcchar(&tester->graphchars[24], L"⣿", 0, 0, NULL);
}

t_rolling_keystat *create_tenkey_struct(size_t first, size_t last, size_t start, int nkeys)
{
	t_rolling_keystat *out = ft_calloc(1, sizeof(t_rolling_keystat));

	out->speed = (nkeys * 1000.0 * 60.0) / ((last - first) * 5.0);
	out->time = last - start;
	return (out);
}

t_list	*get_rolling_keystats(t_inplog *inplog, int nkeys)
{
	t_list		*rolling_keystats = NULL;
	t_inplog	*first;
	t_inplog	*last;
	size_t		start_time;

	if (inplog == NULL)
		return (NULL);
	start_time = inplog->time;
	first = inplog;
	last = inplog;
	for (int i = nkeys - 1; last != NULL && i > 0; i--)
		last = last->next;
	while (last != NULL)
	{
		while (first->input == BACKSPACE)
			first = first->next;
		while (last->input == BACKSPACE)
		{
			last = last->next;
			if (last == NULL)
				return (rolling_keystats);
		}
		ft_lstadd_back(&rolling_keystats, ft_lstnew(create_tenkey_struct(first->time, last->time, start_time, nkeys)));
		first = first->next;
		last = last->next;
	}
	return (rolling_keystats);
}

void	interpolate_points(t_graph graph)
{
	double	*points = graph.points;
	size_t	i = 0;
	size_t	j;
	size_t	diff;
	double	step;

	while (points[i] == 0)
		i++;
	while (i < graph.n_points)
	{
		if (points[i] == 0)
		{
			j = i;
			while (points[j] == 0)
				j++;
			if (points[j] == -1)
			{
				while (i < j)
				{
					points[i] = -1;
					i++;
				}
			}
			diff = j - i + 1;
			step = (points[j] - points[i - 1]) / diff;
			while (i < j)
			{
				points[i] = points[i - 1] + step;
				i++;
			}
		}
		else
			i++;
	}
}

double	get_min_speed(t_graph graph)
{
	double	min = 10000.0;
	double	cur;

	for (size_t i = 0; i < graph.n_points; i++)
	{
		cur = graph.points[i];
		if (cur > 0 && cur < min)
			min = cur;
	}
	return (min);
}

double	get_max_speed(t_graph graph)
{
	double	max = 0.0;
	double	cur;

	for (size_t i = 0; i < graph.n_points; i++)
	{
		cur = graph.points[i];
		if (cur != 0 && cur > max)
			max = cur;
	}
	return (max);
}

void	normalise_points(t_graph *graph)
{
	double	max;
	double	min;
	int		floor;
	int		ceiling;

	max = get_max_speed(*graph);
	min = get_min_speed(*graph);

	int round = 5;
	floor = ((int)min / round) * round;
	ceiling = (((int)max / round) + 1) * round;

	double	scalar = (double)(graph->height - 1) / (ceiling - floor);

	for (size_t i = 0; i < graph->n_points; i++)
		graph->normalised[i] = (graph->points[i] - floor) * scalar + 0.5;
	graph->floor = floor;
	graph->ceiling = ceiling;
	graph->scalar = scalar;
	size_t	i = 0;
	for (; graph->points[i] == 0; i++)
		;
	if (i == 0)
		return ;
	graph->normalised[i - (i % 2 == 0)] = graph->height;
}

void	plot_points(t_graph *graph, t_list *tenkey_avg)
{
	t_rolling_keystat	*stat;
	t_list			*current;

	graph->n_points = (graph->width - 7) * 2;
	graph->points = ft_calloc(graph->n_points + 1, sizeof(double));
	graph->normalised = ft_calloc(graph->n_points + 1, sizeof(double));
	graph->points[graph->n_points] = -1.0;
	graph->normalised[graph->n_points] = -1.0;
	stat = ft_lstlast(tenkey_avg)->content;
	graph->period = stat->time;

	double	step = (double)stat->time / graph->n_points;
	double	current_time = 0;

	current = tenkey_avg;
	size_t	i = 0;
	stat = current->content;
	while (current != NULL && i < graph->n_points)
	{
		while (current_time > stat->time)
		{
			graph->points[i] = stat->speed;
			current = current->next;
			stat = current->content;
		}
		current_time += step;
		i++;
	}
	interpolate_points(*graph);
	// size_t	height = 205;
	// size_t	fifth = graph->n_points / 5;
	// for (size_t i = 0; i < graph->n_points; i++)
	// {
	// 	if (i != 0 && i % fifth == 0)
	// 		height -= 10;
	// 	graph->points[i] = height;
	// 	if (i == graph->n_points - 1)
	// 		graph->points[i] = 100.0;
	// }
	normalise_points(graph);
}

int	count_inputs(t_inplog *pre, t_inplog *post)
{
	t_inplog	*current = pre->next;
	int			i = 0;

	while (current != post)
	{
		current = current->next;
		if (current->input != BACKSPACE)
			i++;
	}
	return (i);
}

void	plot_points_time(t_typer *tester, t_graph *graph)
{
	
	graph->n_points = (graph->width - 7) * 2;
	graph->points = ft_calloc(graph->n_points + 1, sizeof(double));
	graph->normalised = ft_calloc(graph->n_points + 1, sizeof(double));
	graph->points[graph->n_points] = -1.0;
	graph->normalised[graph->n_points] = -1.0;

	size_t	start_time = tester->start_time;
	size_t	step = (tester->end_time - start_time) / graph->n_points;

	t_inplog	*pre_inp = tester->inplog;
	t_inplog	*post_inp = pre_inp;
	size_t		i;
	double		cum_time = 0;

	size_t	window_size = tester->options.graph_win_size;
	for (i = 0; cum_time < window_size; i++)
		cum_time += step;
	size_t	window_end = cum_time;
	size_t	window_start = window_end - window_size;
	for (; i < graph->n_points; i++)
	{
		while (pre_inp->next != NULL && pre_inp->next->time - start_time < window_start)
			pre_inp = pre_inp->next;
		while (post_inp != NULL && post_inp->time - start_time < window_end)
			post_inp = post_inp->next;
		if (pre_inp->next == NULL || post_inp == NULL)
			break ;
		int 	inputs = count_inputs(pre_inp, post_inp);
		graph->points[i] = (inputs * 60000.0) / (5.0 * window_size);
		window_start += step;
		window_end += step;
	}
	// endwin();
	// for (i = 0; i < graph->n_points; i++)
	// 	printf("time: %ld speed: %.1f\n", i * step, graph->points[i]);
	// cleanup(tester);
	// exit(0);
	normalise_points(graph);
}

int	get_num_dots(double point, int height)
{
	if (point >= height)
		return (4);
	if (point < height - 1)
		return (0);

	double mod = fmod(point, 1.0);
	if (mod <= 0.25)
		return (1);
	if (mod <= 0.5)
		return (2);
	if (mod <= 0.75)
		return (3);
	return (4);
}

cchar_t	*get_graph_char(t_typer *tester, double *points, int height)
{
	int	left = get_num_dots(points[0], height);
	int	right = get_num_dots(points[1], height);

	return (&tester->graphchars[left * 5 + right]);
}

void	draw_graph_column(t_typer *tester, t_graph graph, int column)
{
	int		i;
	double	*points = &graph.normalised[column * 2];
	cchar_t *graphchar;

	// graphchar = get_graph_char(tester, points, 1);
	// attron(A_UNDERLINE);
	// mvadd_wch(graph.y + graph.height - 1 , column + graph.x + 6, graphchar);
	// attroff(A_UNDERLINE);
	i = 0;
	while (i < graph.height)
	{
		graphchar = get_graph_char(tester, points, i + 1);
		mvadd_wch(graph.y + graph.height - i - 1 , column + graph.x + 6, graphchar);
		i++;
	}
	// while ((graphchar = get_graph_char(tester, points, i + 1)) != &tester->graphchars[0])
	// {
	// 	// graphchar = get_graph_char(tester, points, i + 1);
	// 	mvadd_wch(graph.y + graph.height - i - 1 , column + graph.x + 6, graphchar);
	// 	i++;
	// }
}

void	draw_graph(t_typer *tester, int line)
{
	t_list	*rolling = NULL;
	t_graph	graph;
	
	graph.x = 1;
	graph.y = 1;
	graph.width = tester->env->win_width - 2;
	graph.height = line - 3;
	if (tester->options.graph_type == 0)
	{
		rolling = get_rolling_keystats(tester->inplog, tester->options.rolling_key_window);
		if (rolling == NULL)
			return ;
		plot_points(&graph, rolling);
	}
	else
		plot_points_time(tester, &graph);

	int	graph_col = tester->options.graph_type == 0 ? MAGENTA_FG : GREEN_FG;
	attrset(COLOR_PAIR(graph_col));
	for (int i = 0; i < graph.width - 7; i++)
	{
		if (graph.points[i * 2] == 0 && graph.normalised[i * 2 + 1] == graph.height)
		{
			attrset(COLOR_PAIR(DEFAULT_COLS));
			draw_graph_column(tester, graph, i);
			attrset(COLOR_PAIR(graph_col));
		}
		else
			draw_graph_column(tester, graph, i);
	}
	attrset(COLOR_PAIR(DEFAULT_COLS));
	mvvline_set(graph.y, graph.x + 5, &tester->boxchars[0], graph.height);
	for (int i = 0; i < graph.height; i++)
	{
		if (i % 2 != 0)
		{
			// if (i == graph.height / 2 || i - 1 == graph.height / 2)
			// {
			// 	attrset(COLOR_PAIR(CYAN_FG));
			// 	mvprintw(graph.y + graph.height - 1 - i, graph.x + 1, "WPM ");
			// 	attrset(COLOR_PAIR(DEFAULT_COLS));
			// }
			continue ;
		}
		int label = round(graph.floor + (i / graph.scalar));
		mvprintw(graph.y + graph.height - 1 - i, graph.x + 1, "%3d ", label);
		add_wch(WACS_RTEE);
	}
	size_t step = (tester->end_time - tester->start_time) / graph.n_points;
	int	height = graph.y + graph.height;
	mvadd_wch(height, graph.x + 5, WACS_LTEE);
	mvprintw(height + 1, graph.x + 4, "0.0");
	for (int i = 1; i < graph.width - 6; i++)
	{
		if (i % 11 != 0 || i == graph.width - 7)
		{
			mvadd_wch(height, graph.x + 5 + i, WACS_HLINE);
			continue ;
		}
		double label = (step * ((i * 2) - 1)) / 1000.0;
		mvadd_wch(height, graph.x + 5 + i, WACS_TTEE);
		char buf[10];
		snprintf(buf, 10, "%.1f", label);
		centre_str(buf, height + 1, (graph.x + 5 + i) * 2 + 1);
		printw("%.1fs", label);
		// if (i + 7 < graph.width / 2 && i + 18 >= graph.width / 2)
		// {
		// 	attrset(COLOR_PAIR(CYAN_FG));
		// 	mvprintw(height + 1, graph.x + 9 + i, "TIME");
		// 	attrset(COLOR_PAIR(DEFAULT_COLS));
		// }
	}
	mvadd_wch(0, tester->env->win_width - 22, WACS_RTEE);
	attrset(A_BOLD);
	printw(" Window: ");
	if (tester->options.graph_type == 1)
	{
		attrset(COLOR_PAIR(graph_col) | A_BOLD);
		printw("%5ld ", tester->options.graph_win_size);
		attrset(COLOR_PAIR(DEFAULT_COLS) | A_NORMAL);
		printw("ms ");
	}
	else
	{
		attrset(COLOR_PAIR(graph_col) | A_BOLD);
		printw(" %2d ", tester->options.rolling_key_window);
		attrset(COLOR_PAIR(DEFAULT_COLS) | A_NORMAL);
		printw("Keys ");
	}
	add_wch(WACS_LTEE);
	if (rolling != NULL)
		ft_lstclear(&rolling, free);
	free(graph.points);
	free(graph.normalised);
}
