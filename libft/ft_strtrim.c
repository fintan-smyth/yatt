/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:08:08 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/02 13:33:13 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		i;
	char	*out;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	if (i > ft_strlen(s1))
	{
		out = malloc(1);
		if (out == NULL)
			return (NULL);
		out[0] = 0;
		return (out);
	}
	s1 += i;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	out = malloc(end + 2);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, s1, end + 2);
	return (out);
}
/*
int	main(void)
{
	char	*s1 = "./,-+++this is a . / + test string-/.,+";
	char	*s2 = "test2-+/";
	char	*s3 = "-/.+tes+3";
	char	*s4 = "-.,+---";
	char	*set = "./,-+";

	printf("<%s>\n", ft_strtrim(s1, set));
	printf("<%s>\n", ft_strtrim(s2, set));
	printf("<%s>\n", ft_strtrim(s3, set));
	printf("<%s>\n", ft_strtrim(s4, set));
}
*/
