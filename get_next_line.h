/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:24:49 by nrumpfhu          #+#    #+#             */
/*   Updated: 2024/10/17 19:28:05 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_remainder(char *dest);
char	*create_line(char *dest);
char	*ft_free(char *dest, char *buf, int join_temp);
char	*read_lines(int fd, char *dest, char *buf);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);

#endif
