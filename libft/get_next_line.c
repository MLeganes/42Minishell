/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorcill <amorcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:27:36 by amorcill          #+#    #+#             */
/*   Updated: 2021/11/22 13:30:16 by amorcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_update_buff(char *buff)
{
	int		index;
	size_t	x;
	size_t	len;
	char	*line;

	len = gnl_strlen(buff);
	index = gnl_find_index(buff, '\n');
	line = gnl_substr(buff, 0, index + 1);
	x = 0;
	while (x <= len)
	{
		buff[x] = buff[index + x + 1];
		x++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*fd_buff;
	char		*line;
	int			bytes_readed;
	char		buff[BUFFER_SIZE + 1];

	while (gnl_find_index(fd_buff, '\n') == -1)
	{		
		bytes_readed = read(fd, buff, BUFFER_SIZE);
		if (bytes_readed <= 0)
		{
			if (fd_buff != NULL && fd_buff[0] == '\0')
			{
				free(fd_buff);
				fd_buff = NULL;
				return (NULL);
			}
			line = fd_buff;
			fd_buff = NULL;
			return (line);
		}
		buff[bytes_readed] = '\0';
		fd_buff = gnl_strjoin(fd_buff, buff);
	}
	line = gnl_update_buff(fd_buff);
	return (line);
}
