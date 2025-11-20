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

char *read_to_stash(char **stash, int fd, char *buffer)
{
    ssize_t bytes_read;
    char *line;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        line = process(stash, buffer, bytes_read);
        if (line)
            return line;
    }
    if (bytes_read < 0) // read error
    {
        free(*stash);
        *stash = NULL;
        return NULL;
    }
    // leftover stash without newline
    if (*stash && **stash)
        return empty_stash(stash);
    return NULL;
}
char *get_next_line(int fd)
{
    static char *stash;
    char *buffer;
    char *line;
    int newline_pos;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return NULL;

    if (stash)
    {
        newline_pos = find_newline(stash);
        if (newline_pos >= 0)
        {
            line = extract_line(&stash, newline_pos);
            free(buffer);
            return line;
        }
    }
    line = read_to_stash(&stash, fd, buffer);
    free(buffer);
    return line;
}

// read into buffer and pass buffer read into a stash
// process every line
// if end of file return the stash;


int main(void)
{
	int fd = open("text.txt", O_RDONLY);
   char *line;
  
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}