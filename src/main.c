
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
#include <limits.h>
#include <locale.h>
#include <ncurses.h>

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

void	init_std_punc(t_punc *standard)
{
	int	i;

	standard->weights = ft_calloc(P_MAX + 1, sizeof(int));
	standard->weights[P_COMMA] = 5;
	standard->weights[P_FSTOP] = 5;
	standard->weights[P_SQUOTE] = 5;
	standard->weights[P_DQUOTE] = 5;
	standard->weights[P_PAREN] = 5;
	standard->weights[P_BRACK] = 5;
	standard->weights[P_BRACE] = 5;
	standard->weights[P_ANGBRACK] = 5;
	standard->weights[P_EXCLAM] = 5;
	standard->weights[P_QUEST] = 5;
	i = -1;
	standard->sum_weights = 0;
	while (++i < P_MAX)
		standard->sum_weights += standard->weights[i];
	standard->weights[P_MAX] = -42;
	standard->prob = 30;
}

void	init_clang_punc(t_punc *clang)
{
	int	i;

	clang->weights = ft_calloc(C_MAX + 1, sizeof(int));
	clang->weights[C_STRUC_ARROW] = 5;
	clang->weights[C_STRUC_DOT] = 5;
	clang->weights[C_FUNC] = 5;
	clang->weights[C_HEADER] = 5;
	clang->weights[C_ARRAY] = 5;
	clang->weights[C_DEREF] = 5;
	clang->weights[C_ADDR] = 5;
	clang->weights[C_ENDL] = 5;
	clang->weights[C_NOT] = 2;
	clang->weights[C_AND] = 2;
	clang->weights[C_OR] = 2;
	clang->weights[C_EQ] = 2;
	clang->weights[C_LT] = 2;
	clang->weights[C_GT] = 2;
	clang->weights[C_LTE] = 2;
	clang->weights[C_GTE] = 2;
	clang->weights[C_BSLEFT] = 2;
	clang->weights[C_BSRIGHT] = 2;
	clang->weights[C_PREINC] = 2;
	clang->weights[C_POSTINC] = 2;
	clang->weights[C_PREDEC] = 2;
	clang->weights[C_POSTDEC] = 2;
	i = -1;
	clang->sum_weights = 0;
	while (++i < C_MAX)
		clang->sum_weights += clang->weights[i];
	clang->weights[C_MAX] = -42;
	clang->prob = 40;
}

void	init_default_options(t_options *options)
{
	init_lang_paths(options);
	setup_default_fingers(options);
	options->kmode = KMODE_INSTRUCT;
	options->cur_lang = options->lang_paths;
	options->num_words = 30;
	options->punc = PMODE_OFF;
	options->full_keyboard = 0;
	options->numbers = 0;
	options->number_prob = 20;
	init_clang_punc(&options->clang);
	init_std_punc(&options->standard);
}

void	init(t_typer *tester)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(*env));
	srand(get_time_ms());
	store_term_settings(env);
	set_term_settings(env);
	set_winsize(env);
	setlocale(LC_ALL, "");
	initscr();
	setcchar(&tester->boxchars[0], L"│", 0, 0, NULL);
	setcchar(&tester->boxchars[1], L"─", 0, 0, NULL);
	setcchar(&tester->boxchars[2], L"╭", 0, 0, NULL);
	setcchar(&tester->boxchars[3], L"╮", 0, 0, NULL);
	setcchar(&tester->boxchars[4], L"╰", 0, 0, NULL);
	setcchar(&tester->boxchars[5], L"╯", 0, 0, NULL);
	setcchar(&tester->boxchars[6], L"├", 0, 0, NULL);
	setcchar(&tester->boxchars[7], L"┤", 0, 0, NULL);
	use_default_colors();
	start_color();
	init_pair(DEFAULT_COLS, -1, -1);
	init_pair(BLACK_FG, COLOR_BLACK, -1);
	init_pair(RED_FG, COLOR_RED, -1);
	init_pair(GREEN_FG, COLOR_GREEN, -1);
	init_pair(YELLOW_FG, COLOR_YELLOW, -1);
	init_pair(BLUE_FG, COLOR_BLUE, -1);
	init_pair(MAGENTA_FG, COLOR_MAGENTA, -1);
	init_pair(CYAN_FG, COLOR_CYAN, -1);
	init_pair(WHITE_FG, COLOR_WHITE, -1);
	init_pair(BLACK_BG, -1, COLOR_BLACK);
	init_pair(RED_BG, COLOR_BLACK, COLOR_RED);
	init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_BG, COLOR_BLACK, COLOR_YELLOW);
	init_pair(BLUE_BG, COLOR_BLACK, COLOR_BLUE);
	init_pair(MAGENTA_BG, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(CYAN_BG, COLOR_BLACK, COLOR_CYAN);
	init_pair(WHITE_BG, COLOR_BLACK, COLOR_WHITE);
	tester->env = env;
	env->min_height = MIN_HEIGHT_SMALL;
	env->min_width = MIN_WIDTH_SMALL;
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
	clear_wordlist(&tester->wordlist);
	reset_term_settings(tester->env);
	free(tester->options.clang.weights);
	free(tester->options.standard.weights);
	free(tester->env);
	ft_lstclear(&tester->options.lang_paths, free);
}

void	handle_errors(t_typer *tester, int errcode)
{
	cleanup(tester);
	if (errcode == E_SYNTAX)
		printf("Invalid argument provided\n");
	else if (errcode == E_TOOMANYWORDS)
		printf("The maximum word count is 500\n");
	else if (errcode == E_NOWORDS)
		printf("The minimum word count is 1\n");
	else if (errcode == E_MISSINGARG)
		printf("Argument not provided\n");
	else if (errcode == E_DOUBLEDEF)
		printf("Config error: option defined multiple times\n");
	else if (errcode == E_CONFIGERR)
		printf("Config error: failed to parse config\n");
	else if (errcode == E_OPENFILE)
		printf("Config error: failed to open config file\n");
	else if (errcode == E_INVALIDOPT)
		printf("Config error: invalid option provided\n");
	else if (errcode == E_TOOMANYWORDS_CFG)
		printf("Config error: The maximum word count is 500\n");
	else if (errcode == E_NOWORDS_CFG)
		printf("Config error: The minimum word count is 1\n");
	else if (errcode == E_HELP)
		print_help();
	exit(1);
}

int main(int argc, char **argv)
{
	t_typer	*tester = &(t_typer){};
	int		retval;

	init(tester);
	tester->lang = load_language_file(tester->options.cur_lang->str);
	if ((retval = parse_config(tester, "default.cfg")) != E_SUCCESS)
		handle_errors(tester, retval);
	if ((retval = handle_args(argc, argv, tester)) != E_SUCCESS)
		handle_errors(tester, retval);
	// char c;
	// while ((c = getchar_nb(tester, render_game)) != ESC)
	// {
	// 	addch(c);
	// 	refresh();
	// }
	// cleanup(tester);
	// exit(0);
	// draw_borders(tester);
	// refresh();
	// getchar();
	// game_loop(tester);
	run_game(tester);
	endwin();
	cleanup(tester);
}
