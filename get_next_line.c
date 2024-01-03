/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:13:57 by louismdv          #+#    #+#             */
/*   Updated: 2024/01/03 17:35:32 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	ssize_t		read_ptr;
	static char	buff[BUFFER_SIZE + 1];
	char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_ptr = 1;
	if (ft_strlen(buff) > 0)
	{
		stash = ft_strdup(buff);
	}
	else
		stash = NULL;
	while ((ft_strchr(buff, '\n')) == 0 && read_ptr != 0)
	{
		read_ptr = read(fd, buff, BUFFER_SIZE);
		if (read_ptr == -1)
			return (0);
		buff[read_ptr] = '\0';
		if (stash == NULL)
			stash = ft_strdup(buff);
		else
			stash = ft_strjoin(stash, buff);
	}
	return (extract_line(stash, read_ptr, buff));
}

char	*extract_line(char *stash, ssize_t read_ptr, char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (stash != NULL && read_ptr != 0)
	{
		while (stash[i] && stash[i] != '\n')
			i++;
		if (stash[i] == '\n')
			i++;
		line = (char *)malloc(sizeof(char) * (i + 1));
		if (!line)
			return (NULL);
		ft_strlcpy(line, stash, i + 1);
		if (ft_strchr(buff, '\n') != 0)
			ft_strcpy(buff, ft_strchr(buff, '\n') + 1);
		free(stash);
		return (line);
	}
	else if (read_ptr == 0 && ft_strlen(stash) < 1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	str = get_next_line(fd);
// 	printf("%s\n", str);
// 	close(fd);
// 	free(str);
// }
