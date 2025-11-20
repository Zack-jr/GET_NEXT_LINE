/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 06:03:59 by zalabib-          #+#    #+#             */
/*   Updated: 2025/11/20 15:05:45 by zalabib-         ###   ########.fr       */
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
    static char *stash[1024];
    char *buffer;
    char *line;
    int newline_pos;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return NULL;

    if (stash[fd])
    {
        newline_pos = find_newline(stash[fd]);
        if (newline_pos >= 0)
        {
            line = extract_line(&stash[fd], newline_pos);
            free(buffer);
            return line;
        }
    }
    line = read_to_stash(&stash[fd], fd, buffer);
    free(buffer);
    return line;
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
