/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalabib- <zalabib-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:29:56 by zalabib-          #+#    #+#             */
/*   Updated: 2025/11/20 14:47:02 by zalabib-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;
	int		len;

	len = 0;
	if (str == NULL)
		return (NULL);
	while (str[len])
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, s1, len1);
	ft_strncpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

void	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return ;
	while (src[i] != '\0' && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line(char **stash, int pos)
{
	char	*res;
	char	*new_stash;
	int		len;

	len = pos + 1;
	res = malloc(sizeof(char) * (len) + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, *stash, len);
	res[len] = '\0';
	new_stash = ft_strdup(*stash + len);
	if (!new_stash)
		return (NULL);
	free(*stash);
	*stash = new_stash;
	return (res);
}
