
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
		if (words > 250)
			return (2);
		if (words < 1)
			return (3);
		tester->options.num_words = words;
	}
	else
		return (1);
	return (0);
}

int	extract_arg_words(t_typer *tester, char *arg)
{
	int		words;
	char	*endptr;

	errno = 0;
	words = ft_strtol(arg, &endptr, 10);
	if (*endptr != 0 || errno != 0)
		return (E_SYNTAX);
	if (words > 250)
		return (E_TOOMANYWORDS);
	if (words < 1)
		return (E_NOWORDS);
	tester->options.num_words = words;
	return (E_SUCCESS);
}

int	extract_arg_punc(t_typer *tester, char *arg)
{
	int	pmode;

	if (ft_strncmp(arg, "off", 4) == 0)
		pmode = PMODE_OFF;
	else if (ft_strncmp(arg, "std", 4) == 0)
		pmode = PMODE_STD;
	else if (ft_strncmp(arg, "c", 2) == 0)
		pmode = PMODE_CLANG;
	else
		return (E_SYNTAX);
	tester->options.punc = pmode;
	return (E_SUCCESS);
}

int	extract_arg_num(t_typer *tester, char *arg)
{
	if (ft_strcmp(arg, "on") == 0
		|| ft_strcmp(arg, "yes") == 0
		|| ft_strcmp(arg, "y") == 0
		|| ft_strcmp(arg, "1") == 0)
		tester->options.numbers = 1;
	else if (ft_strcmp(arg, "off") == 0
		|| ft_strcmp(arg, "no") == 0
		|| ft_strcmp(arg, "n") == 0
		|| ft_strcmp(arg, "0") == 0)
		tester->options.numbers = 0;
	else
		return (E_SYNTAX);
	return (E_SUCCESS);
}

int	extract_arg_kmode(t_typer *tester, char *arg)
{
	if (ft_strcmp(arg, "acc") == 0
		|| ft_strcmp(arg, "accuracy") == 0
		|| ft_strcmp(arg, "a") == 0
		|| ft_strcmp(arg, "0") == 0)
		tester->options.kmode = KMODE_ACC;
	else if (ft_strcmp(arg, "i") == 0
		|| ft_strcmp(arg, "instructional") == 0
		|| ft_strcmp(arg, "instruct") == 0
		|| ft_strcmp(arg, "1") == 0)
		tester->options.kmode = KMODE_INSTRUCT;
	else
		return (E_SYNTAX);
	return (E_SUCCESS);
}

void	print_help(void)
{
	printf("Yet Another Typing Test\n\n");
	printf("\e[1;4mUsage:\e[24m yatt\e[m [OPTIONS]\n\n");
	printf("\e[1;4mOptions:\e[m\n");
	printf("\e[1m  -w, --words\e[m <1-500>\t\tProvide word count [default: 30]\n");
	printf("\e[1m  -p, --punc\e[m <off|std|c>\tSpecify punctuation style to use\n");
	printf("\e[1m  -n, --numbers\e[m <off|on>\tSpecify if numbers are included in tests\n");
	printf("\e[1m  -k, --keyboard\e[m <a|i>\t\tChoose on-screen keyboard style [accuracy/instructional]\n");
	printf("\e[1m  -h, --help\e[m\t\t\tPrint help\n");
}

int	handle_args_new(int argc, char **argv, t_typer *tester)
{
	int	i;
	int	retval;
	int	(*extract_arg)(t_typer *, char *);

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "-w") == 0 || ft_strcmp(argv[i], "--words") == 0)
			extract_arg = extract_arg_words;
		else if (ft_strcmp(argv[i], "-p") == 0 || ft_strcmp(argv[i], "--punc") == 0)
			extract_arg = extract_arg_punc;
		else if (ft_strcmp(argv[i], "-n") == 0 || ft_strcmp(argv[i], "--numbers") == 0)
			extract_arg = extract_arg_num;
		else if (ft_strcmp(argv[i], "-k") == 0 || ft_strcmp(argv[i], "--keyboard") == 0)
			extract_arg = extract_arg_kmode;
		else if (ft_strcmp(argv[i], "-h") == 0 || ft_strcmp(argv[i], "--help") == 0)
			return (E_HELP);
		else
			return (E_SYNTAX);
		if (argv[i + 1] == NULL)
			return (E_MISSINGARG);
		retval = extract_arg(tester, argv[i + 1]);
		if (retval != E_SUCCESS)
			return (retval);
		i += 2;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_typer	*tester = &(t_typer){};
	int		retval;

	init(tester);
	tester->lang = load_language_file(tester->options.cur_lang->str);
	if ((retval = handle_args_new(argc, argv, tester)) != E_SUCCESS)
	{
		cleanup(tester);
		if (retval == E_SYNTAX)
			printf("Invalid argument provided\n");
		else if (retval == E_TOOMANYWORDS)
			printf("The maximum word count is 500\n");
		else if (retval == E_NOWORDS)
			printf("The minimum word count is 1\n");
		else if (retval == E_MISSINGARG)
			printf("Argument not provided\n");
		else if (retval == E_HELP)
			print_help();
		return (1);
	}
	game_loop(tester);;
	cleanup(tester);
}
