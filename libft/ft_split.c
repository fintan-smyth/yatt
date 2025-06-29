/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:29:51 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/22 15:52:20 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strs(char const *s, char c)
{
	int	i;
	int	no_strs;
	int	in_str;

	i = 0;
	in_str = 0;
	no_strs = 0;
	while (s[i] != 0)
	{
		if (in_str == 0 && s[i] != c)
		{
			in_str = 1;
			no_strs++;
		}
		if (in_str == 1 && s[i] == c)
			in_str = 0;
		i++;
	}
	return (no_strs);
}

static char	*alloc_string(const char *s, char c)
{
	int		len;
	char	*out;

	if (ft_strchr(s, c) != NULL)
		len = ft_strchr(s, c) - s;
	else
		len = ft_strlen(s);
	out = malloc(len + 1);
	ft_strlcpy(out, s, len + 1);
	return (out);
}

void	free_split(char ***strings)
{
	int	i;

	i = 0;
	while ((*strings)[i] != NULL)
		free((*strings)[i++]);
	free(*strings);
	*strings = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		no_strs;
	char	**out;
	int		i;

	no_strs = count_strs(s, c);
	out = malloc((no_strs + 1) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		out[i] = alloc_string(s, c);
		s += ft_strlen(out[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}
/*
int	main(void)
{
	char	**out = ft_split("hello,this,is,a,,,test,,,,", ',');
	int		i;

	i = 0;
	while (out[i] != NULL)
		printf("<%s>\n", out[i++]);
}
*/
