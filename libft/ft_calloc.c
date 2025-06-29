/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:00:12 by fsmyth            #+#    #+#             */
/*   Updated: 2024/11/29 12:27:26 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;
	size_t	alloc_size;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	alloc_size = size * nmemb;
	if ((alloc_size / size) != nmemb)
		return (NULL);
	out = malloc(alloc_size);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < alloc_size)
		((char *) out)[i++] = 0;
	return (out);
}
