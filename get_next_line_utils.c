/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:38 by myanez-p          #+#    #+#             */
/*   Updated: 2022/12/01 16:16:23 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	while (str[size] != '\0')
		size ++;
	return (size);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	result = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i ++;
	}
	result[i] = '\0';
	return (result);
}

char	**split_stash(char *stash, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(2 * sizeof(char *));
	if (!result)
		return (NULL);
	while (stash[i] != c)
		i++;
	result[0] = malloc((i + 1 + 1) * sizeof(char));
	result[1] = malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!result[0] || !result[1])
		return (NULL);
	i = -1;
	while (stash[++i] != c)
		result[0][i] = stash[i];
	result[0][i] = c;
	result[0][i + 1] = '\0';
	i ++;
	while (stash[i])
		result[1][j++] = stash[i++];
	result[1][j] = '\0';
	return (result);
}
