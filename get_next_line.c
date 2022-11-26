/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:32:37 by melanieyane       #+#    #+#             */
/*   Updated: 2022/11/18 16:32:22 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(int fd)
{
	size_t		len;
	char		*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	len = read(fd, buffer, BUFFER_SIZE);
	buffer[len] = '\0';
	//printf("%s", buffer);
	return (buffer);
}

int	main(void)
{
	int		fd;
	char	*result;

	fd = open("haricotvert.txt", O_RDONLY);
	result = "";
	while (read(fd, result, BUFFER_SIZE))
	{
		result = get_buffer(fd);
		printf("%s\n", result);
	}
	return (0);
}
