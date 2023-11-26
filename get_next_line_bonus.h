/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:45:04 by aautin            #+#    #+#             */
/*   Updated: 2023/11/26 16:23:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

void	ft_free(void *mem);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_freenullreturn(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2, char free);
char	*get_next_line(int fd);

#endif