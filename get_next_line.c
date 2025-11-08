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

// read line from file referenced by file descriptor one line at a time
// get to know how many times i should read with buffer_size
// must return the line even if the buffer size is shorter than the line
// 

// using cc -D defines a macro for the size of the buffer


// we want to include newline each line but not if end of file

size_t newline_check(const char *str)
{
    size_t pos;
    size_t flag;

    flag = 0;
    pos = 0;
    while (str[pos])
    {
        if (str[pos] == '\n')
        {
            flag = 1;
            return (pos);
        }
        pos++;
    }
    if (flag = 0)
        return (flag);
}
// know if there is a \n, if yes, give position, if not

// addkadaddkd\n
//zzzzz
// abcd
// 

void    get_next_line(int fd)
{
    char str[BUFFER_SIZE];

    read(fd, str, BUFFER_SIZE);

    printf("%s", str);
    
}
// after setting up the buffer for the read
// in each loop, allocate memory for n bytes, and read n bytes
// check if the buffer string contains a \n
// if it does, null truncate the buffer at position buffer[pos + 1] 
// then free and return the buffer

int main(void)
{
    int fd = open("textinput.txt", O_RDWR);

    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);



}

// in main
// open to get file descriptor 
// while my line is not NULL
// print and close (deallocate)the file descriptor