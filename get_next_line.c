/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:23:47 by myanez-p          #+#    #+#             */
/*   Updated: 2022/12/09 14:26:35 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		**result;
	char		*line;
	char		*buffer;
	int			len;

	result = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	add_to_buffer(fd, &buffer, &len);
	while (len > 0 && check_stash(buffer, '\n') == -1)
	{
		add_to_stash(buffer, &stash);
		add_to_buffer(fd, &buffer, &len);
	}
	if (check_stash(buffer, '\n') != -1)
	{
		add_to_stash(buffer, &stash);
		result = extract_line(stash, '\n');
		line = result[0];
		stash = result[1];
		return (line);
	}
	if (ft_strlen(stash) > 0)
	{
		if (check_stash(stash, '\n') == -1)
		{
			line = ft_strdup(stash);
			free(stash);
			stash = NULL;
		}
		if (check_stash(stash, '\n') != -1)
		{
			result = extract_line(stash, '\n');
			line = result[0];
			stash = result[1];
		}
		return (line);
	}
	return (NULL);
}

void	add_to_buffer(int fd, char **buffer, int *len)
{
	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buffer))
		return ;
	*len = read(fd, *buffer, BUFFER_SIZE);
	if (len < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
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
	size_t	i;

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
/*
int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	fd = open("files/41_with_nl", O_RDONLY);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	line = get_next_line(fd);
	printf("line %s\n", line);
	return (0);
}
*/