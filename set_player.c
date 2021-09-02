/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:09:49 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 21:16:23 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_player(t_vars *vars)
{
	int		x;
	int		i;
	int		j;

	i = -1;
	x = 0;
	while (++i < vars->map.height)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (vars->map.map[i][j] == 'W' || vars->map.map[i][j] == 'N' || \
				vars->map.map[i][j] == 'S' || vars->map.map[i][j] == 'E')
			{
				x++;
				vars->plr.nwse = vars->map.map[i][j];
				vars->map.map[i][j] = '0';
				vars->plr.posx = i + 0.5;
				vars->plr.posy = j + 0.5;
			}
			j++;
		}
	}
	if (x != 1)
		exit(error_return("invalid count of players"));
}

void		set_player(t_vars *vars)
{
	set_player_se(vars);
	set_player_nw(vars);
}

void		set_player_se(t_vars *vars)
{
	if (vars->plr.nwse == 'S')
	{
		vars->plr.dirx = 0.0000001;
		vars->plr.diry = -1;
		vars->ray.planex = -0.66;
		vars->ray.planey = 0;
	}
	if (vars->plr.nwse == 'E')
	{
		vars->plr.dirx = -1;
		vars->plr.diry = 0.0000001;
		vars->ray.planex = 0;
		vars->ray.planey = 0.66;
	}
}

void		set_player_nw(t_vars *vars)
{
	if (vars->plr.nwse == 'W')
	{
		vars->plr.dirx = -0.0000001;
		vars->plr.diry = 1;
		vars->ray.planex = 0.66;
		vars->ray.planey = 0;
	}
	if (vars->plr.nwse == 'N')
	{
		vars->plr.dirx = 1;
		vars->plr.diry = 0.0000001;
		vars->ray.planex = 0;
		vars->ray.planey = -0.66;
	}
}
