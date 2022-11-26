/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:38:01 by melanieyane       #+#    #+#             */
/*   Updated: 2022/11/18 17:19:26 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0) //ajouter la condition read
		return (NULL);
	stash = "";
	line = "";
	len = 1;
	add_to_buffer(fd, &stash, &len);
	return (line);
}

void	add_to_buffer(int fd, char **stash, int *len)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	*len = read(fd, buffer, BUFFER_SIZE);
	buffer[*len] = '\0';
	add_to_stash(stash, buffer, len);
}

int	is_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i ++;
	}
	return (0);
}

int main(void)
{
	int 	fd;
	char	*result;

	fd = open("haricotvert.txt", O_RDONLY);
	while (1)
	{
		result = get_next_line(fd);
		printf("%s", result);
		if (result == NULL)
			break ;
		//free(result);
	}
	return (0);
}
