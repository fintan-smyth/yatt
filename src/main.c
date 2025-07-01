/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:37:32 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/27 13:23:38 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"

t_lang	load_language_file(char	*filename)
{
	int		fd;
	char	*line;
	char	*nl_ptr;
	t_list	*word_list = NULL;
	t_lang	lang;

	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if ((nl_ptr = ft_strchr(line, '\n')) != NULL)
			*nl_ptr = '\0';
		ft_lstadd_back(&word_list, ft_lstnew(line));
	}
	lang.size = ft_lstsize(word_list);
	lang.words = (char **)ft_lst_to_arr(word_list);
	ft_lstclear(&word_list, NULL);
	close(fd);
	return (lang);
}

void	init(t_typer *tester)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	srand(get_time_ms());
	store_term_settings(env);
	set_term_settings(env);
	set_winsize(env);
	tester->env = env;
}

void	cleanup(t_typer *tester)
{
	free_split(&tester->lang.words);
	reset_term_settings(tester->env);
	free(tester->env);
}

int	handle_args(int argc, char **argv, t_typer *tester)
{
	long	words;
	char	*endptr;

	errno = 0;
	if (argc == 1)
		tester->num_words = 30;
	else if (argc == 2)
	{
		words = ft_strtol(argv[1], &endptr, 10);
		if (*endptr != 0 || errno != 0)
			return (1);
		if (words > 500)
			return (2);
		if (words < 1)
			return (3);
		tester->num_words = words;
	}
	else
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_typer	*tester = &(t_typer){};
	int	retval;

	init(tester);
	tester->lang = load_language_file("./lang/english1000");
	if ((retval = handle_args(argc, argv, tester)) != 0)
	{
		if (retval == 1)
			printf("Please provide a valid word count\n");
		else if (retval == 2)
			printf("The maximum word count is 500\n");
		else if (retval == 3)
			printf("The minimum word count is 1\n");
		return (cleanup(tester), 1);
	}
	game_loop(tester);;
	cleanup(tester);
}
