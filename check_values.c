/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:20:16 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:05:19 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	nullify_values(t_vars *vars)
{
	vars->flags.flr = 0;
	vars->flags.ceil = 0;
	vars->flags.spr = 0;
	vars->flags.so = 0;
	vars->flags.we = 0;
	vars->flags.no = 0;
	vars->flags.ea = 0;
	vars->map.iter = 0;
	vars->flags.res = 0;
	vars->evt.forward = 0;
	vars->evt.back = 0;
	vars->evt.mvright = 0;
	vars->evt.mvleft = 0;
	vars->evt.left = 0;
	vars->evt.right = 0;
	vars->flags.save = 0;
	vars->flags.save = 0;
}

void	check_argv(char **argv, t_vars *vars)
{
	if (vars->argc != 3 && vars->argc != 2)
		exit(error_return("Invalid number of arguments\n"));
	else if (vars->argc == 3 && ft_strncmp(argv[1], "--save", 7) == 0)
	{
		vars->flags.save = 1;
		check_cub(vars, argv[2], 2);
	}
	else if (vars->argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		vars->flags.save = 1;
		check_cub(vars, argv[1], 1);
	}
	else if (vars->argc == 3)
		exit(error_return("Invalid arguments\n"));
	else
		check_cub(vars, argv[1], 1);
}

void	check_cub(t_vars *vars, char *str, int k)
{
	int		i;

	i = ft_strlen(str) - 4;
	if (ft_strncmp(str + i, ".cub", 4) != 0)
		exit(error_return("Invalid map file\n"));
	vars->argc = k;
}
