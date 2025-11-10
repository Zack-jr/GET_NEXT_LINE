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


size_t ft_strlen(char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}

size_t find_newline(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i + 1);
        i++;
    }
    return (0);
}

char     *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE];
    static char *stash;
    char *line;
    char *temp;
    int i;

    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        if (stash == NULL)
            stash = malloc(BUFFER_SIZE + 1);


        stash = strncat(stash, buffer, BUFFER_SIZE);
        i = find_newline(stash);

        if (i > 0)
        {
            line = malloc(sizeof(char) * (ft_strlen(stash)) + 1); // Lorum ips,\nd
            temp = malloc(sizeof(char) * (ft_strlen(stash)) + 1);

            // copy the substring into line
            //line[0] = '\0';
            line = memmove(line, stash, i);
            temp = memmove(temp, stash + i, ft_strlen(stash + i));
            free(stash);
            stash = temp;
            return (line);
        }
    }
    //if (read(fd, buffer, BUFFER_SIZE) == 0)
        //return (NULL);
}
// abcde/nas
// i


int main(void)
{
    int fd = open("textinput.txt", O_RDONLY);
    //printf("%li", find_newline("abdd\ne"));

    int i = 0;
    
    while (i < 20)
    {
       printf("%s", get_next_line(fd));
        i++;
    }

    /*
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    */
    /*
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);*/
}


// in main
// open to get file descriptor 
// while my line is not NULL
// print and close (deallocate)the file descriptor