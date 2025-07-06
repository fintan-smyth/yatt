
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:37:32 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/02 01:18:48 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

char	*extract_lang_name(char *lang_path)
{
	char	*name;

	name = ft_strrchr(lang_path, '/');
	if (name == NULL)
		return (lang_path);
	return (name + 1);
}

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
	lang.name = ft_strdup(extract_lang_name(filename));
	ft_lstclear(&word_list, NULL);
	close(fd);
	return (lang);
}

void	init_lang_paths(t_options *options)
{
	ft_lstadd_back(&options->lang_paths, ft_lstnew(ft_strdup("./lang/english1000")));
	ft_lstadd_back(&options->lang_paths, ft_lstnew(ft_strdup("./lang/english-advanced")));
}

void	init_default_options(t_options *options)
{
	init_lang_paths(options);
	setup_default_fingers(options);
	options->kmode = 1;
	options->cur_lang = options->lang_paths;
	options->num_words = 30;
	options->punc = 0;
	options->brackets = 1;
	options->quotes = 1;
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
	tester->menu_state.no_entries = M_MAX;
	init_default_options(&tester->options);
}

void	cleanup_lang(t_lang *lang)
{
	free_split(&lang->words);
	free(lang->name);
}

void	cleanup(t_typer *tester)
{
	cleanup_lang(&tester->lang);
	reset_term_settings(tester->env);
	free(tester->env);
	ft_lstclear(&tester->options.lang_paths, free);
}

int	handle_args(int argc, char **argv, t_typer *tester)
{
	long	words;
	char	*endptr;

	errno = 0;
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		words = ft_strtol(argv[1], &endptr, 10);
		if (*endptr != 0 || errno != 0)
			return (1);
		if (words > 500)
			return (2);
		if (words < 1)
			return (3);
		tester->options.num_words = words;
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
	tester->lang = load_language_file(tester->options.cur_lang->str);
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
