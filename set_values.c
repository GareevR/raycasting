/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:33:47 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:47:02 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_resolution(t_vars *vars, char **str)
{
	int		num;

	num = 0;
	while (str[num])
		num++;
	if (num != 3)
		exit(error_return("Invalid resolution"));
	check_values(str + 1, "Invalid resolution");
	if (vars->flags.res == 0 || vars->map.iter != 0)
	{
		vars->screen.width = ft_atoi(str[1]);
		vars->screen.height = ft_atoi(str[2]);
		check_resolution(vars);
		vars->flags.res = 1;
	}
	else
		exit(error_return("Invalid resolution"));
}

void	free_arr(char **arr)
{
	int		n;

	n = 0;
	while (arr[n] != NULL)
		free(arr[n++]);
	free(arr);
	arr = NULL;
}

void	check_values(char **arr, char *str)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (arr[i])
	{
		x = 0;
		while (arr[i][x] != '\0')
		{
			if (arr[i][x] < '0' || arr[i][x] > '9')
				exit(error_return(str));
			x++;
		}
		i++;
	}
}

void	check_resolution(t_vars *vars)
{
	if (vars->screen.width < 0 || vars->screen.height < 0)
		exit(error_return("Invalid resolution"));
	if (vars->screen.width > 2560)
		vars->screen.width = 2560;
	if (vars->screen.height > 1440)
		vars->screen.height = 1440;
	if (vars->map.iter != 0)
		vars->zbuffer = (double*)malloc(sizeof(double) * vars->screen.width);
}

void	set_files(t_vars *vars)
{
	vars->tex.img[0] = mlx_xpm_file_to_image(vars->mlx, vars->data.no_path, \
	&vars->tex.width[0], &vars->tex.height[0]);
	vars->tex.addr[0] = mlx_get_data_addr(vars->tex.img[0], &vars->tex.bpp[0], \
	&vars->tex.lnlen[0], &vars->tex.endian[0]);
	vars->tex.img[1] = mlx_xpm_file_to_image(vars->mlx, vars->data.so_path, \
	&vars->tex.width[1], &vars->tex.height[1]);
	vars->tex.addr[1] = mlx_get_data_addr(vars->tex.img[1], &vars->tex.bpp[1], \
	&vars->tex.lnlen[1], &vars->tex.endian[1]);
	vars->tex.img[2] = mlx_xpm_file_to_image(vars->mlx, vars->data.we_path, \
	&vars->tex.width[2], &vars->tex.height[2]);
	vars->tex.addr[2] = mlx_get_data_addr(vars->tex.img[2], &vars->tex.bpp[2], \
	&vars->tex.lnlen[2], &vars->tex.endian[2]);
	vars->tex.img[3] = mlx_xpm_file_to_image(vars->mlx, vars->data.ea_path, \
	&vars->tex.width[3], &vars->tex.height[3]);
	vars->tex.addr[3] = mlx_get_data_addr(vars->tex.img[3], &vars->tex.bpp[3], \
	&vars->tex.lnlen[3], &vars->tex.endian[3]);
	vars->tex.img[4] = mlx_xpm_file_to_image(vars->mlx, vars->data.spr_path, \
	&vars->tex.width[4], &vars->tex.height[4]);
	vars->tex.addr[4] = mlx_get_data_addr(vars->tex.img[4], &vars->tex.bpp[4], \
	&vars->tex.lnlen[4], &vars->tex.endian[4]);
}
