/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphtest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:23:13 by fsmyth            #+#    #+#             */
/*   Updated: 2025/09/14 01:23:53 by fsmyth           ###   ########.fr       */
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

t_tenkey_stat *create_tenkey_struct(size_t first, size_t tenth, size_t start)
{
	t_tenkey_stat *out = ft_calloc(1, sizeof(t_tenkey_stat));

	out->speed = (2.0 * 1000.0 * 60.0) / (tenth - first);
	out->time = tenth - start;
	return (out);
}

t_list	*get_tenkey_stats(t_inplog *inplog)
{
	t_list		*tenkey = NULL;
	t_inplog	*first;
	t_inplog	*tenth;
	size_t		start_time;

	if (inplog == NULL)
		return (NULL);
	start_time = inplog->time;
	first = inplog;
	tenth = inplog;
	for (int i = 9; tenth != NULL && i > 0; i--)
		tenth = tenth->next;
	while (tenth != NULL)
	{
		while (first->input == BACKSPACE)
			first = first->next;
		while (tenth->input == BACKSPACE)
		{
			tenth = tenth->next;
			if (tenth == NULL)
				return (tenkey);
		}
		ft_lstadd_back(&tenkey, ft_lstnew(create_tenkey_struct(first->time, tenth->time, start_time)));
		first = first->next;
		tenth = tenth->next;
	}
	return (tenkey);
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
}

void	plot_points(t_graph *graph, t_list *tenkey_avg)
{
	t_tenkey_stat	*stat;
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
	t_list	*tenkey;
	t_graph	graph;
	
	graph.x = 1;
	graph.y = 1;
	graph.width = tester->env->win_width - 2;
	graph.height = line - 1;
	tenkey = get_tenkey_stats(tester->inplog);
	if (tenkey == NULL)
		return ;
	plot_points(&graph, tenkey);

	attrset(COLOR_PAIR(MAGENTA_FG));
	for (int i = 0; i < graph.width - 7; i++)
		draw_graph_column(tester, graph, i);
	attrset(COLOR_PAIR(DEFAULT_COLS));
	mvvline_set(graph.y, graph.x + 5, &tester->boxchars[0], graph.height);
	// mvprintw(graph.y, graph.x + 1, "%3d ", graph.ceiling);
	// add_wch(WACS_URCORNER);
	// mvprintw(graph.y + graph.height - 1, graph.x + 1, "%3d ", graph.floor);
	// add_wch(WACS_LRCORNER);
	for (int i = 0; i < graph.height; i++)
	{
		if (i % 2 != 0)
			continue ;
		int label = round(graph.floor + (i / graph.scalar));
		mvprintw(graph.y + graph.height - 1 - i, graph.x + 1, "%3d ", label);
		add_wch(WACS_RTEE);
	}
	// int fd = open("./plotlog", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// for (size_t i = 0; i < graph.n_points; i++)
	// 	dprintf(fd, "i: %ld speed: %.1f norm: %.1f\n", i, graph.points[i], graph.normalised[i]);
	// close(fd);
	// printf("tenkey: %p\n", tenkey);
	// for (t_list *current = tenkey; current != NULL; current = current->next)
	// {
	// 	t_tenkey_stat	*stat = current->content;
	// 	printf("time: %5ld speed: %.2f\n", stat->time, stat->speed);
	// }
	// printf("num points: %d\n", ft_lstsize(tenkey));
	// printf("win width: %d\n\n", tester->env->win_width);
	// refresh();
	// char c;
	// while ((c = getch()) != 'q')
	// 	;
	ft_lstclear(&tenkey, free);
	free(graph.points);
	free(graph.normalised);
}
