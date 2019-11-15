/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:12:58 by akhalidy          #+#    #+#             */
/*   Updated: 2019/11/15 00:27:14 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
//#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#define BUFFER_SIZE 5

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



int	get_next_line(int fd, char **line)
{
    char        *buf;
    int         r;
    static char *rest;
    char        *tmp;
    char        *tp;

    if (fd < 0 || BUFFER_SIZE < 0 || 
        !(buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
        return (-1);
    
    if (rest)
	{
        if ((tmp = strchr(rest, '\n')))
        {
            *tmp = '\0';
            *line = ft_strdup(rest);
            tp = rest;
            rest = ft_strdup(tmp + 1);
            free(tp);
            return (1);
        }
	}
	else
    	rest = (char *)ft_calloc(1, sizeof(char));
    
    if (!(buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
        return (-1);
    while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        rest = ft_strjoin(rest, buf);
        if((tmp = ft_strchr(rest, '\n')))
        {
            *tmp = '\0';
            *line = ft_strdup(rest);
            tp= rest;
            rest = ft_strdup(tmp + 1);
            free(tp);
            free(buf);
            return (1);
        }
        ft_bzero(buf, BUFFER_SIZE);
    }
    free (buf);
    //printf("\n|%s| -- |%s|\n", *line, rest);
    if(rest)
    {
        *line = ft_strdup(rest);
        free(rest);
        rest = NULL;
    }
    return (r);
}

/*int main()
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
    //system("leaks a.out");
    int r ;
    char *buf;
    buf = (char *)calloc(5, sizeof(char));
    while ((r = read(fd, buf, 5)))
    {
        printf("buf %d : $%s$\n",++i, buf);
        printf("%d\n",r);
        bzero(buf,strlen(buf));
    }
    printf("buf %d : $%s$\n",++i, buf);
    printf("%d\n",r);
    return (0);
}*/
