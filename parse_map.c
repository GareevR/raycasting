/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:19:11 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 21:16:18 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(int fd, t_vars *vars)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (vars->map.iter++ == 0)
		find_mapscale(fd, vars, line);
	else
		fill_2d_map(fd, vars, line);
}

void	find_mapscale(int fd, t_vars *vars, char *line)
{
	int		i;

	vars->map.height = 0;
	vars->map.width = 0;
	i = 0;
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] != '\0' || vars->map.height > 0)
			vars->map.height++;
		if (vars->map.width < (int)ft_strlen(line))
			vars->map.width = (int)ft_strlen(line);
		free(line);
	}
	if (line)
		free(line);
	if (vars->map.height > 0 && vars->map.width > 0)
	{
		vars->map.map = (char**)malloc(sizeof(char*) * vars->map.height);
		while (i < vars->map.height)
			vars->map.map[i++] = (char*)malloc(sizeof(char) *
			vars->map.width + 1);
	}
}

void	fill_2d_map(int fd, t_vars *vars, char *line)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &line) != 0)
	{
		if ((i != 0 || line[0] != '\0') && vars->map.height > 0
		&& i < vars->map.height)
			copy_line(vars, line, i++);
		free(line);
	}
	if (line)
		free(line);
}
