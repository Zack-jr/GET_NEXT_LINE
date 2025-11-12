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

char     *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE];
    static char *stash;
    char *line;
    char *temp;
    int i;
    ssize_t bytes_read;

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0) // check jusqua eof
    {
        if (stash == NULL) // si variavle statique non initialisee, malloc
        {
            stash = malloc(bytes_read + 1);
            stash[0] = '\0';
        }

        stash = strncat(stash, buffer, bytes_read); // copier buffer dans la reserve
        i = find_newline(stash); // donner position de la newline

        if (i >= 0) // si newline
        {
            line = malloc(i + 1); // allouer memoire pour la taille de la reserve
            temp = malloc(sizeof(char) * (ft_strlen(stash + i)) + 1); // pareil

            line = memmove(line, stash, i); // copier reserve dans line jusqu'au \n
    
            temp = memmove(temp, stash + i, ft_strlen(stash + i)); // nouveau pointeur pour free la stash
            temp[ft_strlen(stash + i ) + 1] = '\0';
            free(stash);
            stash = temp; // mettre a l'adresse de la nouvelle ligne
            return (line);
        }
   
        if (bytes_read == 0 && *stash && stash)
        {
            line = malloc(ft_strlen(stash) + 1);
            line = memmove(line, stash, (ft_strlen(stash)));
            line[ft_strlen(stash)] = '\0'; 
            free(stash);
            stash = NULL;
            return line;
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    return NULL;
}
// abcde/nas
// i


int main(void)
{
    int fd = open("textinput.txt", O_RDONLY);
    //printf("%li", find_newline("abdd\ne"));

    int i = 0;
    
    while (i < 5)
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