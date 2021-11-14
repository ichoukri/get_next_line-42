/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichoukri <ichoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:53:05 by ichoukri          #+#    #+#             */
/*   Updated: 2021/11/10 20:14:03 by ichoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*change_result(char *result)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = 0;
	while (result[len] != '\n' && result[len] != '\0')
		len++;
	if (result[len] == '\0')
	{
		free(result);
		return (NULL);
	}
	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(result) - len + 1));
	if (dest == NULL)
		return (NULL);
	while (result[++len] != '\0')
		dest[i++] = result[len];
	dest[i] = '\0';
	free(result);
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	i = -1;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (dest == NULL)
		return (NULL);
	while (++i < s1_len)
		dest[i] = s1[i];
	while (j <= s2_len)
		dest[i++] = s2[j++];
	free(s1);
	return (dest);
}

char	*ft_read(char *result, int fd)
{
	char	*buff;
	int		n;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	n = 1;
	while (ft_strchr(result, '\n') == NULL && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[n] = '\0';
		result = ft_strjoin(result, buff);
	}
	free(buff);
	return (result);
}

char	*get_line(char *result)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	if (result[0] == '\0')
		return (NULL);
	while (result[len] != '\n' && result[len] != '\0')
		len++;
	if (result[len] == '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = result[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*result[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result[fd] = ft_read(result[fd], fd);
	if (result[fd] == NULL)
		return (NULL);
	line = get_line(result[fd]);
	result[fd] = change_result(result[fd]);
	return (line);
}
