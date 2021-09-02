/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:36:08 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:13:38 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_tex_no(t_vars *vars, char **str)
{
	int		num;
	int		fd;

	num = 0;
	while (str[num])
		num++;
	if (num != 2)
		exit(error_return("invalid NORTH texture"));
	if (ft_strncmp(str[0], "NO", 3) != 0)
		exit(error_return("invalid NORTH texture"));
	if (vars->flags.no == 0 || vars->map.iter != 0)
	{
		if (vars->map.iter == 0)
			vars->data.no_path = ft_strdup(str[1]);
		if ((fd = open(vars->data.no_path, O_RDONLY)) > -1)
			close(fd);
		else if (vars->flags.no != 1)
			exit(error_return("incorrect path to NORTH texture"));
		vars->flags.no = 1;
	}
	else
		exit(error_return("excess NORTH textures"));
}

void	set_tex_so(t_vars *vars, char **str)
{
	int		num;
	int		fd;

	num = 0;
	while (str[num])
		num++;
	if (num != 2)
		exit(error_return("invalid SOUTH texture"));
	if (ft_strncmp(str[0], "SO", 3) != 0)
		exit(error_return("invalid SOUTH texture"));
	if (vars->flags.so == 0 || vars->map.iter != 0)
	{
		if (vars->map.iter == 0)
			vars->data.so_path = ft_strdup(str[1]);
		if ((fd = open(vars->data.so_path, O_RDONLY)) > -1)
			close(fd);
		else if (vars->flags.so != 1)
			exit(error_return("incorrect path to SOUTH texture"));
		vars->flags.so = 1;
	}
	else
		exit(error_return("excess SOUTH textures"));
}

void	set_tex_we(t_vars *vars, char **str)
{
	int		num;
	int		fd;

	num = 0;
	while (str[num])
		num++;
	if (num != 2)
		exit(error_return("invalid WEST texture"));
	if (ft_strncmp(str[0], "WE", 3) != 0)
		exit(error_return("invalid WEST texture"));
	if (vars->flags.we == 0 || vars->map.iter != 0)
	{
		if (vars->map.iter == 0)
			vars->data.we_path = ft_strdup(str[1]);
		if ((fd = open(vars->data.we_path, O_RDONLY)) > -1)
			close(fd);
		else if (vars->flags.we != 1)
			exit(error_return("incorrect path to WEST texture"));
		vars->flags.we = 1;
	}
	else
		exit(error_return("excess WEST textures"));
}

void	set_tex_ea(t_vars *vars, char **str)
{
	int		num;
	int		fd;

	num = 0;
	while (str[num])
		num++;
	if (num != 2)
		exit(error_return("invalid EAST texture"));
	if (ft_strncmp(str[0], "EA", 3) != 0)
		exit(error_return("invalid EAST texture"));
	if (vars->flags.ea == 0 || vars->map.iter != 0)
	{
		if (vars->map.iter == 0)
			vars->data.ea_path = ft_strdup(str[1]);
		if ((fd = open(vars->data.ea_path, O_RDONLY)) > -1)
			close(fd);
		else if (vars->flags.ea != 1)
			exit(error_return("incorrect path to EAST texture"));
		vars->flags.ea = 1;
	}
	else
		exit(error_return("excess EAST textures"));
}

void	set_tex_spr(t_vars *vars, char **str)
{
	int		num;
	int		fd;

	num = 0;
	while (str[num])
		num++;
	if (num != 2)
		exit(error_return("invalid SPRITE"));
	if (ft_strncmp(str[0], "S", 2) != 0)
		exit(error_return("invalid SPRITE"));
	if (vars->flags.spr == 0 || vars->map.iter != 0)
	{
		if (vars->map.iter == 0)
			vars->data.spr_path = ft_strdup(str[1]);
		if ((fd = open(vars->data.spr_path, O_RDONLY)) > -1)
			close(fd);
		else if (vars->flags.spr != 1)
			exit(error_return("incorrect path to SPRITE texture"));
		vars->flags.spr = 1;
	}
	else
		exit(error_return("excess SPRITE textures"));
}
