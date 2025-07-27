/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:08:15 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/24 16:10:20 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"

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

int	handle_args(int argc, char **argv, t_typer *tester)
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


