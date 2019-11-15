/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:12:58 by akhalidy          #+#    #+#             */
/*   Updated: 2019/11/15 01:47:16 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char*)s;
	if ((char)c == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

int		checkrest(char *tmp, char **rest, char **line)
{
	char *tp;

	if (*rest)
	{
		if ((tmp = ft_strchr(*rest, '\n')))
		{
			*tmp = '\0';
			*line = ft_strdup(*rest);
			tp = *rest;
			*rest = ft_strdup(tmp + 1);
			free(tp);
			return (1);
		}
	}
	else
		*rest = (char *)ft_calloc(1, sizeof(char));
	return (0);
}

int		getn(int fd, char **rest, char *tmp, char **line)
{
	int		r;
	char	*buf;
	char	*tp;

	if (!(buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
		return (-1);
	while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		*rest = ft_strjoin(*rest, buf);
		if ((tmp = ft_strchr(*rest, '\n')))
		{
			*tmp = '\0';
			*line = ft_strdup(*rest);
			tp = *rest;
			*rest = ft_strdup(tmp + 1);
			free(tp);
			free(buf);
			return (1);
		}
		ft_bzero(buf, BUFFER_SIZE);
	}
	free(buf);
	return (r);
}

int		get_next_line(int fd, char **line)
{
	int			rd;
	static char *rest;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (-1);
	tmp = NULL;
	if (checkrest(tmp, &rest, line))
		return (1);
	rd = getn(fd, &rest, tmp, line);
	if (rd == 1)
		return (1);
	if (rest && rd != -1)
	{
		*line = ft_strdup(rest);
		free(rest);
		rest = NULL;
	}
	return (rd);
}
int main()
{
    char *line;
    int i = 0;
    int fd; 
    int r;
    fd = open("file.txt",O_RDONLY);
    while ((r = get_next_line(fd, &line)) > 0)
    {
        printf("line %d : $%s$\n",++i, line);
        free (line);
    }
    printf("line %d : |%s|\n",++i, line);
    free (line);
    close(fd);
    return(0);
}