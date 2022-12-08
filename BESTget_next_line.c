/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:23:47 by myanez-p          #+#    #+#             */
/*   Updated: 2022/12/08 14:44:52 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

void	add_to_buffer(int fd, char **buffer, size_t *len);
void	add_to_stash(char *buffer, char **stash);
char	**extract_line(char *stash, char c);
int		check_stash(char *stash, char c);

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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		**result;
	char		*line;
	char		*buffer;
	size_t		len;

	result = NULL;
	buffer = NULL;
	add_to_buffer(fd, &buffer, &len);
	while (len > 0)
	{
		add_to_stash(buffer, &stash);
		if (check_stash(stash, 'x') != -1)
		{
			result = extract_line(stash, 'x');
			line = result[0];
			stash = result[1];
			return (line);
		}
		else
		{
			return (stash);
		}
		add_to_buffer(fd, &buffer, &len);
	}
	if (ft_strlen(stash) > 0)
	{
		line = ft_strdup(stash);
		stash = NULL;
		return (line);
	}
	return (NULL);
}

void	add_to_buffer(int fd, char **buffer, size_t *len)
{
	*buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*len = read(fd, *buffer, BUFFER_SIZE);
	(*buffer)[BUFFER_SIZE] = '\0';
}

void	add_to_stash(char *buffer, char **stash)
{
	if (!(*stash))
		*stash = malloc(sizeof(char) * (ft_strlen(*stash) + ft_strlen(buffer)));
	ft_strcat(*stash, buffer);
}

char	**extract_line(char *stash, char c)
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

int	check_stash(char *stash, char c)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (-1);
	while (i < ft_strlen(stash))
	{
		if (stash[i] == c)
			return (i);
		i ++;
	}
	return (-1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*buffer;

	fd = open("haricot_vert.txt", O_RDONLY);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	buffer = get_next_line(fd);
	printf("line %s\n", buffer);
	return (0);
}
