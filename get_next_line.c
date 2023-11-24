/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:44:07 by aautin            #+#    #+#             */
/*   Updated: 2023/11/24 22:09:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_afterline(char *str, char freed)
{
	int		i;
	int		len;
	int		start;
	char	*substr;

	start = 0;
	while (str[start] != '\n' && str[start])
		start++;
	if (str[start])
		start++;
	len = 0;
	while (str[len + start])
		len++;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
	{
		if (freed && str)
			free(str);
		return (NULL);
	}
	substr[len] = '\0';
	i = 0;
	while (i < len)
	{
		substr[i] = str[i + len];
		i++;
	}
	if (freed && str)
		free(str);
	return (substr);
}

static char	*ft_get_beforeline(char *str, char freed)
{
	int		i;
	int		len;
	char	*substr;

	len = 0;
	while (str[len] != '\n' && str[len])
		len++;
	if (str[len])
		len++;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[len] = '\0';
	i = 0;
	while (i < len)
	{
		substr[i] = str[i];
		i++;
	}
	if (freed && str)
		free(str);
	return (substr);
}

static long int	ft_read_and_protect(int fd, char *buffer_str, long int size)
{
	long int readchars_nb;

	readchars_nb = read(fd, buffer_str, size);
	if (readchars_nb < 0)
		buffer_str[0] = '\0';
	else
		buffer_str[readchars_nb] = '\0';
	return (readchars_nb);
}

char	*get_next_line(int fd)
{
	char		*buffer_str;
	char		*line;
	static char	*temp;
	int			readchars;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	if (temp != NULL)
		line = ft_strjoin(temp, "\0", 1);
	else
		line = ft_strjoin("\0", "\0", 0);
	while (!ft_strchr(line, '\n'))
	{
		buffer_str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer_str)
		{
			free(line);
			return (NULL);
		}
		readchars = ft_read_and_protect(fd, buffer_str, BUFFER_SIZE);
		if (readchars <= 0)
		{
			free(buffer_str);
			free(line);
			return (NULL);
		}
		line = ft_strjoin(line, buffer_str, 3);
		if (readchars != BUFFER_SIZE)
		{
			if (!ft_strchr(line, '\n'))
				line = ft_strjoin(line, "\n", 1);
			else
			{
				temp = ft_get_afterline(line, 0);
				line = ft_get_beforeline(line, 1);
			}
			return (line);
		}
	}
	temp = ft_get_afterline(line, 0);
	line = ft_get_beforeline(line, 1);
	return (line);
}
