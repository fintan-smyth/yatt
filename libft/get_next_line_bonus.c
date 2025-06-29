/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:23:41 by fsmyth            #+#    #+#             */
/*   Updated: 2024/12/05 00:54:32 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static void	extend_line(char **line, char *buf)
{
	size_t	buflen;
	size_t	linelen;
	char	*temp;

	linelen = 0;
	if (buf[0] == 0)
		return ;
	buflen = 0;
	while (buf[buflen] && buflen < BUFFER_SIZE)
		buflen++;
	if (*line != NULL)
	{
		linelen = ft_strlen(*line);
		temp = malloc(buflen + linelen + 1);
		ft_strlcpy(temp, *line, buflen + linelen + 1);
		free(*line);
	}
	else
		temp = malloc(buflen + 1);
	ft_strlcpy(&temp[linelen], buf, buflen + 1);
	*line = temp;
}

static size_t	line_from_buf(char **line, char *buf)
{
	size_t	len;
	char	*temp;

	len = 0;
	while (buf[len] != '\n' && buf[len] != 0 && len < BUFFER_SIZE)
		len++;
	if (buf[len] == '\n')
		len++;
	if (len == 0)
		return (len);
	temp = malloc(len + 1);
	ft_memset(temp, 0, len + 1);
	ft_strlcpy(temp, buf, len + 1);
	temp[len] = 0;
	extend_line(line, temp);
	ft_memmove(buf, &buf[len], BUFFER_SIZE - len);
	ft_memset(&buf[BUFFER_SIZE - len], 0, len);
	free(temp);
	return (len);
}

char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE] = {0};
	char		*line;
	ssize_t		nread;

	line = NULL;
	nread = BUFFER_SIZE;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	if (buf[fd][0] == 0)
		nread = read(fd, buf[fd], BUFFER_SIZE);
	if (nread <= 0)
		return (NULL);
	while (ft_strchr(buf[fd], '\n') == NULL && nread == BUFFER_SIZE)
	{
		extend_line(&line, buf[fd]);
		nread = read(fd, buf[fd], BUFFER_SIZE);
		if (nread < 0)
			return (line);
	}
	if (nread < BUFFER_SIZE)
		buf[fd][nread] = 0;
	line_from_buf(&line, buf[fd]);
	return (line);
}
