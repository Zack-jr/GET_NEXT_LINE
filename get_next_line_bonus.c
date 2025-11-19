/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 06:03:59 by zalabib-          #+#    #+#             */
/*   Updated: 2025/11/19 06:20:19 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h> 
#include <stdio.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
// return index of new line

char	*extract_line(char **stash, int pos)
{
	char	*res;
	char	*new_stash;
	int len;
	len = pos + 1;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strncpy(res, *stash, len);
	res[len] = '\0';
	new_stash = ft_strdup(*stash + len);
	free(*stash);
	*stash = new_stash;
	return (res);
}
// malloc for the line, copy until newline and null terminate
// remove line from stash and free its characters

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
// null terminate the buffer
// if i have a stash, join the next buffer to the stash and free previous stash
// if i don't, duplicate buffer into stash
// if newline, extract the line

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

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[1024];
	ssize_t		bytes_read;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (stash[fd])
	{
		i = find_newline(stash[fd]);
		if (i >= 0)
		{
			line = extract_line(&stash[fd], i);
			free(buffer);
			return (line);
		}
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line = process(&stash[fd], buffer, bytes_read);
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
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (stash[fd] && *stash[fd])
		return (empty_stash(&stash[fd]));
	free(stash[fd]);
	stash[fd] = NULL;
	return (NULL);
}

/*
int main(void)
{
	int fd = open("text.txt", O_RDONLY);
    int fd2 = open("text2.txt", O_RDONLY);
    char *line = get_next_line(fd);
    char *line2 = get_next_line(fd2);
  
	while (line2)
    {
        printf("%s", line2);
        free(line2);
        line2 = get_next_line(fd2);
    }
    free(line2);
    printf("\n");
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
	
	close(fd);
    close (fd2);
}*/
