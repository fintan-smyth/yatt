/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:27:32 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/29 15:49:03 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf_bonus.h"

// char	*ft_strndup(const char *str, size_t n)
// {
// 	char	*out;
//
// 	out = malloc(n + 1);
// 	if (out == NULL)
// 		return (NULL);
// 	ft_strlcpy(out, str, n + 1);
// 	return (out);
// }

char	*ft_join_or_start(char *s1, char *s2)
{
	char	*output;

	if (s1 != NULL && s2 != NULL)
	{
		output = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	else if (s2 != NULL)
		output = s2;
	else if (s1 != NULL)
		output = s1;
	else
		output = NULL;
	return (output);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
