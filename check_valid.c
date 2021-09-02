/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:10:38 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 21:31:53 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	check_grid(vars);
	check_player(vars);
	count_sprites(vars);
	set_sprites(vars);
	check_xpm(vars);
	set_player(vars);
	while (i < vars->map.height)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			check_srnd(vars, i, j);
			j++;
		}
		i++;
	}
}

void	check_xpm(t_vars *vars)
{
	int		x;

	x = ft_strlen(vars->data.ea_path) - 4;
	if (ft_strncmp(vars->data.ea_path + x, ".xpm", 4) != 0)
		exit(error_return("Invalid EAST texture extension"));
	x = ft_strlen(vars->data.so_path) - 4;
	if (ft_strncmp(vars->data.so_path + x, ".xpm", 4) != 0)
		exit(error_return("Invalid SOUTH texture extension"));
	x = ft_strlen(vars->data.no_path) - 4;
	if (ft_strncmp(vars->data.no_path + x, ".xpm", 4) != 0)
		exit(error_return("Invalid NORTH texture extension"));
	x = ft_strlen(vars->data.we_path) - 4;
	if (ft_strncmp(vars->data.we_path + x, ".xpm", 4) != 0)
		exit(error_return("Invalid WEST texture extension"));
	x = ft_strlen(vars->data.spr_path) - 4;
	if (ft_strncmp(vars->data.spr_path + x, ".xpm", 4) != 0)
		exit(error_return("Invalid SPRITE extension"));
}

void	check_srnd(t_vars *vars, int i, int j)
{
	if ((vars->map.map[i][j] == '0' || vars->map.map[i][j] == 'W' ||
		vars->map.map[i][j] == 'N' || vars->map.map[i][j] == 'S' ||
		vars->map.map[i][j] == 'E' || vars->map.map[i][j] == '4') &&
		i != 0 && i != vars->map.height - 1 && j != 0)
	{
		if (!vars->map.map[i - 1][j - 1] || !vars->map.map[i + 1][j + 1] ||
			!vars->map.map[i + 1][j] || !vars->map.map[i][j + 1] ||
			!vars->map.map[i - 1][j] || !vars->map.map[i][j - 1] ||
			!vars->map.map[i - 1][j + 1] || !vars->map.map[i + 1][j - 1] ||
			vars->map.map[i - 1][j] == ' ' || vars->map.map[i][j - 1] == ' ' ||
			vars->map.map[i + 1][j] == ' ' || vars->map.map[i][j + 1] == ' ' ||
			vars->map.map[i - 1][j - 1] == ' ' ||
			vars->map.map[i + 1][j + 1] == ' ' ||
			vars->map.map[i - 1][j + 1] == ' ' ||
			vars->map.map[i + 1][j - 1] == ' ')
			exit(error_return("INVALID MAP"));
	}
	else if (vars->map.map[i][j] != '1' && vars->map.map[i][j] != ' ' &&
			(i == 0 || i == vars->map.height - 1 || j == 0))
		exit(error_return("INVALID MAP"));
}

int		error_return(char *str)
{
	ft_putstr_fd(str, 1);
	return (-1);
}

void	check_grid(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (!(vars->map.map[i][j] == '1' || vars->map.map[i][j] == '0' ||
				vars->map.map[i][j] == 'W' || vars->map.map[i][j] == 'N' ||
				vars->map.map[i][j] == 'S' || vars->map.map[i][j] == 'E' ||
				vars->map.map[i][j] == '2' || vars->map.map[i][j] == ' '))
				exit(error_return("Invalid map"));
			vars->map.sprites++;
			j++;
		}
		i++;
	}
}
