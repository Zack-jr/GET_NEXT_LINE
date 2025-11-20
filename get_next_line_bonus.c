/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:29:59 by zalabib-          #+#    #+#             */
/*   Updated: 2025/11/20 15:08:20 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include <stdio.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*process(char **stash, char *buffer, size_t bytes_read)
{
	int		i;
	char	*tmp;

	i = 0;
	if (bytes_read == 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (*stash)
	{
		tmp = ft_strjoin(*stash, buffer);
		if (!tmp)
			return (NULL);
		free(*stash);
		*stash = tmp;
	}
	else
	{
		*stash = ft_strdup(buffer);
		if (!*stash)
			return (NULL);
	}
	i = find_newline(*stash);
	if (i >= 0)
		return (extract_line(stash, i));
	return (NULL);
}

char	*empty_stash(char	**stash)
{
	char	*line;

	line = NULL;
	if (*stash)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}
// empty last stash;

char	*read_to_stash(char **stash, int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*line;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		line = process(stash, buffer, bytes_read);
		if (line)
			return (line);
	}
	if (bytes_read < 0)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	if (*stash && **stash)
		return (empty_stash(stash));
	return (NULL);
}

char	*loop(int fd, char *buffer, char *line, char **stash)
{
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line = process(stash, buffer, bytes_read);
		if (line)
		{
			free(buffer);
			return (line);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	if (*stash && **stash)
		return (empty_stash(stash));
	free(*stash);
	*stash = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;
	int			newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (stash[fd])
	{
		newline_pos = find_newline(stash[fd]);
		if (newline_pos >= 0)
		{
			line = extract_line(&stash[fd], newline_pos);
			free(buffer);
			return (line);
		}
	}
	return (loop(fd, buffer, NULL, &stash[fd]));
}

// read into buffer and pass buffer read into a stash
// process every line
// if end of file return the stash;

/*
int main(void)
{
	int fd = open("text.txt", O_RDONLY);
   char *line;

   line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
}
*/