/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:55:41 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/01 21:35:22 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_match(int *i, int *start, int *end)
{
	*start = 0;
	*end = 0;
	*i = -1;
}

static void	check_start_end(char *wc, char wchar, int *start, int *end)
{
	if (ft_strchr(wc, wchar) == wc)
		*start = 1;
	if (ft_strrchr(wc, wchar) == (wc + ft_strlen(wc) - 1))
		*end = 1;
}

int	ft_match_wc(char *str, char *wc, char wchar)
{
	char	**match;
	char	*found;
	int		start;
	int		end;
	int		i;

	init_match(&i, &start, &end);
	check_start_end(wc, wchar, &start, &end);
	match = ft_split(wc, wchar);
	while (match[++i] != NULL)
	{
		found = ft_strnstr(str, match[i], ft_strlen(str));
		if (found != NULL)
		{
			if (i == 0 && start == 0 && found != str)
				return (free_split(&match), 0);
			else if (match[i + 1] == NULL && end == 0
				&& *(found + ft_strlen(match[i])) != 0)
				return (free_split(&match), 0);
			str = found + ft_strlen(match[i]);
		}
		else
			return (free_split(&match), 0);
	}
	return (free_split(&match), 1);
}
