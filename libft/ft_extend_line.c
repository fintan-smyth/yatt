/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:10 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/14 18:51:23 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_extend_line(char *line, char *extra)
// returns 'line' with 'extra' added to the end.
// If replaced, the old 'line' is freed
{
	char	*out;

	if (line == NULL && extra == NULL)
		return (NULL);
	if (line == NULL)
		return (ft_strdup(extra));
	if (extra == NULL)
		return (line);
	out = ft_strjoin(line, extra);
	free(line);
	return (out);
}
