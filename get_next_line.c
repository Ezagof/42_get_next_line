/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:44:07 by aautin            #+#    #+#             */
/*   Updated: 2023/11/23 21:51:59 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_afterline(char *str)
{
	int		i;
	char	*substr;

	while (*str != '\n')
		str++;
	str++;
	i = 0;
	while (str[i])
		i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[i] = '\0';
	while (--i >= 0)
		substr[i] = str[i];
	free(str);
	return (substr);
}

static char	*ft_get_beforeline(char *str)
{
	int		i;
	char	*substr;

	i = 0;
	while (str[i] != '\n')
		i++;
	i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[i] = '\0';
	while (--i >= 0)
		substr[i] = str[i];
	free(str);
	return (substr);
}

char	*get_next_line(int fd)
{
	char		*buffer_str;
	char		*line;
	static char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0  || read(fd, 0, 0) < 0)
		return (NULL);
	if (temp != NULL && *temp != '\0')
	{
		buffer_str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer_str == NULL)
			return (NULL);
		buffer_str[BUFFER_SIZE] = '\0';
		line = ft_strjoin(temp, "");
		free(temp);
	}
	else
	{
		buffer_str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer_str == NULL)
			return (NULL);
		read(fd, buffer_str, BUFFER_SIZE);
		buffer_str[BUFFER_SIZE] = '\0';
		line = ft_strjoin(buffer_str, "");
	}
	while (!ft_strchr(line, '\n'))
	{
		temp = ft_strjoin(line, "");
		free(line);
		if (read(fd, buffer_str, BUFFER_SIZE) < 0)
		{
			line = ft_strjoin(temp, buffer_str);
			free(temp);
			temp = ft_strjoin(line, "\n");
			free(line);
			free(buffer_str);
			return (temp);
		}
		else
			line = ft_strjoin(temp, buffer_str);
		free(temp);
	}
	temp = ft_get_afterline(buffer_str);
	line = ft_get_beforeline(line);
	return (line);
}
