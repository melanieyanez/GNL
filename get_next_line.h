/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:35 by myanez-p          #+#    #+#             */
/*   Updated: 2022/11/26 16:03:45 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <ctype.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
void	add_to_buffer(int fd, char **buffer);
void	add_to_stash(char *buffer, char **stash);
int		check_stash(char *stash);
size_t	ft_strlen(char const *str);
char	*ft_strcat(char *dest, char *src);
char	*ft_strdup(const char *s1);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	extract_line(int fd, char **stash, char **line);
char	**split_stash(char *stash, char c);

#endif