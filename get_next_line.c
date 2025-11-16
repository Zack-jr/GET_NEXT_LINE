/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-05 16:29:59 by zalabib-          #+#    #+#             */
/*   Updated: 2025-11-05 16:29:59 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// strncat to concatenate stash + next buffer

// return line from a file using file descriptor
// have a loop that will read into the buffer while 
// declare a buffer that will store the reading of each read call
// create a stash that will store the string in the buffer
// read and check stash until my stash contains a new line
// if it contains a new line, put the previous characters including the \n from the stash into the result string
// remove the extracted string from the stash
// string copy to trim beginning of string


// "abcd\ne"


size_t ft_strlen(const char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}

ssize_t find_newline(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i + 1);
        i++;
    }
    return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
    char *old_str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
    old_str = s1;
	if (!str)
		return (NULL);
	while (*s1 != '\0')
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
    free(old_str);
	return (str);
}
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char *process_line(char **stash, int fd, char *buffer, int pos, int flag)
{
    char *line;
    char *new_stash;

    if (flag = 1)
    {
        line = malloc((sizeof(char) * pos ) + 1);
        if (!line)
            return (NULL);
        line = strncpy(line, stash[fd], pos);
        line[pos] = '\0';
        new_stash = ft_strdup(stash[fd] + pos);
        free(stash[fd]);
        stash[fd] = new_stash;
        free(buffer);
        return (line);
    }

}

char     *get_next_line(int fd)
{
    char *buffer;
    static char *stash[1025];
    char *line;
    int pos;
    ssize_t bytes_read;

    if ((fd >= 1 && fd <= 2) || fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        if (stash[fd] == NULL)
        {
            stash[fd] = malloc(bytes_read + 1);
            stash[fd][0] = '\0';
        }
        stash[fd] = ft_strjoin(stash[fd], buffer);
        pos = find_newline(stash[fd]); // donner position de la newline
        if (pos > 0) // si newline
            return (process_line(stash, fd, buffer, pos, 1));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    if (stash[fd] && *stash[fd])
    {
        line = ft_strdup(stash[fd]);
        free(stash[fd]);
        stash[fd] = NULL;
        free(buffer);
        return (line);
    }
    return NULL;
}

int main(void)
{
    int fd = open("textinput.txt", O_RDONLY);
    //printf("%li", find_newline("abdd\ne"));
   //int fd2 = open("lyrics.txt", O_RDONLY);
    char *line1;
    //char *line2;
    dup2(fd, 5);
     line1 = get_next_line(5);
     printf("%s", line1);
     free(line1);

    //line2 = get_next_line(fd2);
   /* while (line1 && line2)
    {
        printf("%s", line1);
         free(line1);
        printf("%s", line2);
         free(line2);
        line1 = get_next_line(fd);
        line2 = get_next_line(fd2);
    }*/

    close(fd);

}

// in main
// open to get file descriptor 
// while my line is not NULL
// print and close (deallocate)the file descriptor