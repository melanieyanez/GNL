/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:11 by myanez-p          #+#    #+#             */
/*   Updated: 2022/12/01 18:01:06 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	line = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash)
		line = ft_strcat(line, stash);
	while (check_stash(stash, 'x') == -1)
	{
		add_to_buffer(fd, &buffer);
		sleep(1);
		printf("buffer %s\n", buffer);
		printf("index %d\n", check_stash(buffer, '\0'));
		if (buffer[0] == '\0')
			return (NULL);
		add_to_stash(buffer, &stash);
	}	
	extract_line(fd, &stash, &line);
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
}

void	extract_line(int fd, char **stash, char **line)
{
	char	**result;
	char	*next_buffer;

	result = NULL;
	if (check_stash(*stash, 'x') != -1)
	{
		result = split_stash(*stash, 'x');
		*line = result[0];
		*stash = result[1];
	}
	else
	{		
		add_to_buffer(fd, &next_buffer);
		if (next_buffer == NULL)
			return ;
		add_to_stash(next_buffer, stash);
		return (extract_line(fd, stash, line));
	}
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
