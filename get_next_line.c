/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:33:44 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:21:19 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		get_mem_free(char **str, int exit)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (exit);
}

static char		*get_str_fill(int ret, char *str, char *buf)
{
	char	*temp;

	temp = str;
	*(buf + ret) = '\0';
	str = ft_strjoin(str, buf);
	free(temp);
	temp = NULL;
	return (str);
}

void			get_line_create(char **str, char **line)
{
	char	*n;

	if ((n = ft_strchr(*str, '\n')))
	{
		*line = ft_substr(*str, 0, n - *str);
		*str = ft_strdup(n + 1);
	}
	else
	{
		*line = ft_strdup(*str);
		*str = ft_strdup("");
	}
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	char			*buf;
	char			*temp;
	static char		*str;

	ret = 1;
	if (BUFFER_SIZE <= 0 || fd < 0 || !(line) ||
			(!str && !(str = ft_strdup(""))))
		return (-1);
	if (!(buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while (!(ft_strchr(str, '\n')) && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
		str = get_str_fill(ret, str, buf);
	free(buf);
	if (ret < 0 || !str)
		return (get_mem_free(&str, -1));
	temp = str;
	get_line_create(&str, line);
	free(temp);
	if (!ret && (!*str))
		return (get_mem_free(&str, 0));
	return (1);
}
