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
#include "get_next_line.h"

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

char *extract_line(char **stash, char *buffer)
{
    free(buffer);
    int pos = find_newline(*stash);
    char *line = malloc(pos + 1);
    char *tmp;
    if (!line)
        return NULL;
    strncpy(line, *stash, pos);
    line[pos] = '\0';
    tmp = ft_strdup(*stash + pos);
    free(*stash);
    *stash = tmp;
    return line;
}

char *cat_stash(char *stash, char *buffer)
{
    char *str;
    str = ft_strjoin(stash, buffer);
    free(stash);
    return (str);
}

char *return_stash(char **stash)
{
    char *line = ft_strdup(*stash);
    free(*stash);
    *stash = NULL;
    return line;
}

char     *get_next_line(int fd)
{
    char *buffer;

    static char *stash[1025];
    ssize_t bytes_read;

    if ((fd == 1 || fd == 2) || fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
    {
        buffer[bytes_read] = '\0'; 
        if (stash[fd])
            stash[fd] = cat_stash(stash[fd], buffer);
        else
            stash[fd] = ft_strdup(buffer);
        if (find_newline(stash[fd]) >= 0)
            return extract_line(&stash[fd], buffer);
    }
    free(buffer);
    if (stash[fd] && *stash[fd])
        return (return_stash(&stash[fd]));
    return NULL;
}

int main(void)
{
    int fd = open("textinput.txt", O_RDONLY);
    //printf("%li", find_newline("abdd\ne"));
   //int fd2 = open("lyrics.txt", O_RDONLY);
    char *line1;
   // char *line2;
    //dup2(fd, 5);
     line1 = get_next_line(fd);
        printf("%s", line1);
        free(line1);
     line1 = get_next_line(fd); 
     printf("%s", line1);
     free(line1);
    
     //free(line1);

   // line2 = get_next_line(fd2);
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