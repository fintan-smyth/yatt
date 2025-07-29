/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:11:43 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/24 20:09:05 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yatt.h"
#include <fcntl.h>

void	delimit_token(t_list **tokens, int *token_len, char *buf)
{
	char	*token_str;

	buf[*token_len] = 0;
	token_str = ft_strdup(buf);
	*token_len = 0;
	ft_lstadd_back(tokens, ft_lstnew(token_str));
}

t_list	*tokenise_config(char *filename)
{
	FILE	*file;
	t_list	*tokens = NULL;
	char	buf[1024] = {};
	char	c;
	int		token_len = 0;
	int		quoting = 0;

	file = fopen(filename, "r");
	if (file == NULL)
		return (NULL);

	while ((c = getc(file)) != EOF)
	{
		if (c == '"')
		{
			if (token_len > 0 || quoting)
				delimit_token(&tokens, &token_len, buf);
			quoting = !quoting;
			continue ;
		}
		if (quoting && c == '\\')
		{
			c = getc(file);
			if (c != '"')
			{
				ungetc(c, file);
				c = '\\';
			}
		}
		else if (!quoting && ft_iswhitespace(c))
		{
			if (token_len != 0)
				delimit_token(&tokens, &token_len, buf);
			continue ;
		}
		else if (!quoting && c == '=')
		{
			if (token_len > 0)
				delimit_token(&tokens, &token_len, buf);
			buf[token_len++] = c;
			delimit_token(&tokens, &token_len, buf);
			continue ;
		}
		else if (!quoting && c == '#')
		{
			if (token_len > 0)
				delimit_token(&tokens, &token_len, buf);
			c = getc(file);
			while (c != '\n' && c != EOF)
				c = getc(file);
			ungetc(c, file);
			continue ;
		}
		buf[token_len] = c;
		token_len++;
	}
	if (token_len > 0)
		delimit_token(&tokens, &token_len, buf);
	fclose(file);
	return (tokens);
}

int	get_config_type(char *str)
{
	if (ft_strcmp(str, "words") == 0)
		return (M_WORDS);
	if (ft_strcmp(str, "numbers") == 0)
		return (M_NUMBERS);
	if (ft_strcmp(str, "punc") == 0)
		return (M_PUNC);
	if (ft_strcmp(str, "kmode") == 0)
		return (M_KMODE);
	return (M_MAX);
}

int	config_option_valid(t_list *tokens)
{
	if (tokens->next == NULL)
		return (E_CONFIGERR);
	if (tokens->next->next == NULL)
		return (E_CONFIGERR);
	if (ft_strcmp(tokens->next->str, "=") != 0)
		return (E_CONFIGERR);
	if (get_config_type(tokens->str) == M_MAX)
		return (E_CONFIGERR);
	return (E_SUCCESS);
}

int	apply_option_words(t_typer *tester, char *arg)
{
	int		words;
	char	*endptr;

	errno = 0;
	words = ft_strtol(arg, &endptr, 10);
	if (*endptr != 0 || errno != 0)
		return (E_CONFIGERR);
	if (words > 500)
		return (E_TOOMANYWORDS_CFG);
	if (words < 1)
		return (E_NOWORDS_CFG);
	tester->options.num_words = words;
	return (E_SUCCESS);
}

int	apply_option_punc(t_typer *tester, char *arg)
{
	int	pmode;

	if (ft_strcmp(arg, "off") == 0)
		pmode = PMODE_OFF;
	else if (ft_strcmp(arg, "std") == 0)
		pmode = PMODE_STD;
	else if (ft_strcmp(arg, "c-style") == 0)
		pmode = PMODE_CLANG;
	else
		return (E_INVALIDOPT);
	tester->options.punc = pmode;
	return (E_SUCCESS);
}

int	apply_option_num(t_typer *tester, char *arg)
{
	if (ft_strcmp(arg, "enabled") == 0)
		tester->options.numbers = 1;
	else if (ft_strcmp(arg, "disabled") == 0)
		tester->options.numbers = 0;
	else
		return (E_INVALIDOPT);
	return (E_SUCCESS);
}

int	apply_option_kmode(t_typer *tester, char *arg)
{
	if (ft_strcmp(arg, "accuracy") == 0)
		tester->options.kmode = KMODE_ACC;
	else if (ft_strcmp(arg, "instructional") == 0)
		tester->options.kmode = KMODE_INSTRUCT;
	else
		return (E_INVALIDOPT);
	return (E_SUCCESS);
}

int	apply_config_option(t_typer *tester, t_list *token, int type)
{
	int		retval;
	char	*option;
	char	*arg;

	option = token->str;
	arg = token->next->next->str;
	switch (type){
		case (M_WORDS):
			retval = apply_option_words(tester, arg);
			break ;
		case (M_NUMBERS):
			retval = apply_option_num(tester, arg);
			break ;
		case (M_PUNC):
			retval = apply_option_punc(tester, arg);
			break ;
		case (M_KMODE):
			retval = apply_option_kmode(tester, arg);
			break ;
		default:
			retval = E_CONFIGERR;
			break ;
	}
	return (retval);
}

int	parse_tokens(t_typer *tester, t_list *tokens)
{
	t_list	*current;
	int		config_type;
	int		provided_options[M_MAX] = {};
	int		retval;

	current = tokens;
	while (current != NULL)
	{
		if ((retval = config_option_valid(current)) != E_SUCCESS)
			return (retval);
		config_type = get_config_type(current->str);
		if (provided_options[config_type] != 0)
			return (E_DOUBLEDEF);
		if ((retval = apply_config_option(tester, current, config_type)) != E_SUCCESS)
			return (retval);
		provided_options[config_type] = 1;
		current = current->next->next->next;
	}
	return (E_SUCCESS);
}

int	parse_config(t_typer *tester, char *filename)
{
	t_list	*tokens;
	t_list	*current;
	int		retval;

	tokens = tokenise_config(filename);
	if (tokens == NULL)
		return (E_OPENFILE);

	current = tokens;
	// while (current != NULL)
	// {
	// 	printf("<%s>\n", current->str);
	// 	current = current->next;
	// }
	if ((retval = parse_tokens(tester, tokens)) != E_SUCCESS)
		return (retval);
	ft_lstclear(&tokens, free);
	return (E_SUCCESS);
}
