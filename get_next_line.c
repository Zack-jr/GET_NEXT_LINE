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

char	*extract_line(char **stash, int pos)
{
	char	*res;
	char	*new_stash;
	int		len;

	len = pos + 1;
	res = malloc(sizeof(char) * (len) + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, *stash, len);
	res[len] = '\0';
	new_stash = ft_strdup(*stash + len);
	if (!new_stash)
		return (NULL);
	free(*stash);
	*stash = new_stash;
	return (res);
}

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
	static char	*stash;
	char		*buffer;
	char		*line;
	int			newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (stash)
	{
		newline_pos = find_newline(stash);
		if (newline_pos >= 0)
		{
			line = extract_line(&stash, newline_pos);
			free(buffer);
			return (line);
		}
	}
	return (loop(fd, buffer, NULL, &stash));
}

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