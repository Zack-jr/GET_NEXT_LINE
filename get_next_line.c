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

#include <unistd.h>

// read line from file referenced by file descriptor one line at a time
// must return the line that has been read, if error or nothing to read return NULL
// must be able to read from file or from standard input
// must also return \n at the end of line if not end of file
// must compile with -D BUFFER_SIZE=n



char *get_next_line(int fd)
{
    char  buffer[];
    buffer = BUFFER_SIZE;
    buffer = read(fd, buffer, sizeof(buffer) - 1);
}
