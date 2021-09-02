/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:52:54 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:05:32 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_line(t_vars *vars, char *line, int i)
{
	int		j;

	j = 0;
	if (line[j] == '\0')
		exit(error_return("invalid map\n"));
	while (line[j] != '\0')
	{
		vars->map.map[i][j] = line[j];
		j++;
	}
	while (j < vars->map.width)
	{
		vars->map.map[i][j] = ' ';
		j++;
	}
	vars->map.map[i][j] = '\0';
}

void	parser(char **argv, t_vars *vars)
{
	int		fd;
	char	*line;
	int		num;
	int		ret;

	fd = open((argv[vars->argc]), O_RDONLY);
	if (fd < 0)
		exit(error_return("Invalid map file\n"));
	ret = 1;
	num = 0;
	while (num < 8 && ret != 0)
	{
		ret = get_next_line(fd, &line);
		parse_string(vars, line, &num);
		free(line);
	}
	if (check_info(vars) == 1)
		parse_map(fd, vars);
	else
		exit(error_return("invalid map\n"));
	close(fd);
}

int		check_info(t_vars *vars)
{
	if (vars->flags.res == 1 && vars->flags.no == 1 &&
		vars->flags.so == 1 && vars->flags.we == 1 &&
		vars->flags.ea == 1 && vars->flags.spr == 1 &&
		vars->flags.flr == 1 && vars->flags.ceil == 1)
		return (1);
	return (-1);
}

void	parse_string(t_vars *vars, char *line,
						int *num)
{
	int		i;
	char	**str;

	str = ft_split(line, ' ');
	i = 0;
	if (str == NULL || str[0] == NULL)
		return ;
	if (str[0][0] == 'R')
		set_resolution(vars, str);
	else if (str[0][0] == 'N' && str[0][1] == 'O')
		set_tex_no(vars, str);
	else if (str[0][0] == 'S' && str[0][1] == 'O')
		set_tex_so(vars, str);
	else if (str[0][0] == 'W' && str[0][1] == 'E')
		set_tex_we(vars, str);
	else if (str[0][0] == 'E' && str[0][1] == 'A')
		set_tex_ea(vars, str);
	else if (str[0][0] == 'S')
		set_tex_spr(vars, str);
	else if (str[0][0] == 'F')
		set_floor_clr(vars, str);
	else if (str[0][0] == 'C')
		set_ceil_clr(vars, str);
	free_arr(str);
	*num = *num + 1;
}

void	parse_all(t_vars *vars, char **argv)
{
	nullify_values(vars);
	check_argv(argv, vars);
	parser(argv, vars);
	parser(argv, vars);
	check_map(vars);
}
