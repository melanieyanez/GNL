/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:11 by myanez-p          #+#    #+#             */
/*   Updated: 2022/11/26 16:40:30 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash)
	{
		line = ft_strcat(line, stash);
		free (stash);
	}
	add_to_buffer(fd, &buffer);
	if (buffer[0] == '\0')
		return (NULL);
	add_to_stash(buffer, &stash);
	extract_line(fd, &stash, &line);
	sleep(1);
	return (line);
}

void	add_to_buffer(int fd, char **buffer)
{
	int		len;

	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	len = read(fd, *buffer, BUFFER_SIZE);
	if (len == 0 || len == -1)
	{	
		(*buffer)[0] = '\0';
		return ;
	}
	(*buffer)[BUFFER_SIZE] = '\0';
}

void	add_to_stash(char *buffer, char **stash)
{
	if (!(*stash))
		*stash = malloc(sizeof(char) * (ft_strlen(*stash) + ft_strlen(buffer)));
	ft_strcat(*stash, buffer);
	printf("stash %s\n", *stash);
	free (buffer);
}

void	extract_line(int fd, char **stash, char **line)
{
	char	**result;
	char	*next_buffer;

	result = NULL;
	if (check_stash(*stash) != 0)
	{
		result = split_stash(*stash, '\n');
		*line = result[0];
		*stash = result[1];
	}
	else
	{
		add_to_buffer(fd, &next_buffer);
		if (next_buffer[0] == '\0')
			return ;
		add_to_stash(next_buffer, stash);
		return (extract_line(fd, stash, line));
	}
}

int	check_stash(char *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i ++;
	}
	//return (-1);
	return (0);
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

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	*stash;
	char	*buffer;

	fd = open("haricot_vert.txt", O_RDONLY);
	stash = "";
	line = "";

	
	while (line)
	{
		line = get_next_line(fd);
		printf("line %s\n", line);
		if (line == NULL)
			break ;
	}
	free (line);
	return (0);
}
