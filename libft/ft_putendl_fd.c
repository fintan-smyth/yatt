/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:26:53 by fsmyth            #+#    #+#             */
/*   Updated: 2025/01/27 18:09:17 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	char	*s1 = "test string";

	ft_putendl_fd(s1, 1);
}
*/
