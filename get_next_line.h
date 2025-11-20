/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:30:01 by zalabib-          #+#    #+#             */
/*   Updated: 2025/11/20 14:58:38 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strncpy(char *dst, char *src, int n);
char	*get_next_line(int fd);
int		find_newline(char *str);
char	*extract_line(char **stash, int pos);

#endif