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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		total_len;
	size_t	i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * total_len);
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

char     *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE];
    static char *stash;
    char *line;
    int i;
    ssize_t bytes_read;
    char *new_stash;

    //if (fd == 0 || BUFFER_SIZE == 0)
      //  return (NULL);

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        if (stash == NULL)
        {
            stash = malloc(bytes_read + 1);
            stash[0] = '\0';
        }
        stash = ft_strjoin(stash, buffer);
        i = find_newline(stash); // donner position de la newline
        if (i > 0) // si newline
        {
            line = malloc((sizeof(char) * i ) + 1);
            line = strncpy(line, stash, i);
            line[i] = '\0';
            new_stash = ft_strdup(stash + i);
            free(stash);
            stash = new_stash;
            return (line);
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    if (stash && *stash)
    {
        line = ft_strdup(stash);
        free(stash);
        stash = NULL;
        return (line);
    }
    return NULL;
}

int main(void)
{
    int fd = open("textinput.txt", O_RDONLY);
    //printf("%li", find_newline("abdd\ne"));
    
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        line = get_next_line(fd);
    }
    close(fd);

}

// in main
// open to get file descriptor 
// while my line is not NULL
// print and close (deallocate)the file descriptor