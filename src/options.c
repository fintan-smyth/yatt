/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:15:30 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/01 23:04:53 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "yatt.h"

void	setup_fingers(t_typer *tester)
{
	char			index[] = "rtfgcvbyhnujm";
	char			middle[] = "edxik";
	char			ring[] = "wszol";
	char			pinky[] = "qap";
	char			thumb[] = " ";
	unsigned char	c;

	c = 1;
	while (c <= 127)
	{
		if (ft_strchr(index, c))
		{
			tester->fingers[c] = 1;
			tester->fingers[ft_toupper(c)] = 1;
		}
		else if (ft_strchr(middle, c))
		{
			tester->fingers[c] = 2;
			tester->fingers[ft_toupper(c)] = 2;
		}
		else if (ft_strchr(ring, c))
		{
			tester->fingers[c] = 3;
			tester->fingers[ft_toupper(c)] = 3;
		}
		else if (ft_strchr(pinky, c))
		{
			tester->fingers[c] = 4;
			tester->fingers[ft_toupper(c)] = 4;
		}
		else if (ft_strchr(thumb, c))
		{
			tester->fingers[c] = 5;
			tester->fingers[ft_toupper(c)] = 5;
		}
		c++;
	}
}
