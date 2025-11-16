/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-05 16:30:01 by zalabib-          #+#    #+#             */
/*   Updated: 2025-11-05 16:30:01 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t ft_strlen(const char *str);
char *get_next_line(int fd);

#endif