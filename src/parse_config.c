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
		else if (!quoting && c == '=' && token_len > 0)
			delimit_token(&tokens, &token_len, buf);
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

int	parse_config(t_typer *tester, char *filename)
{
	t_list	*tokens;
	t_list	*current;

	tokens = tokenise_config(filename);
	if (tokens == NULL)
		return (E_OPENFILE);

	current = tokens;
	while (current != NULL)
	{
		printf("<%s>\n", current->str);
		current = current->next;
	}
	ft_lstclear(&tokens, free);
	return (E_SUCCESS);
}
