/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:58:40 by frariel           #+#    #+#             */
/*   Updated: 2021/02/25 17:51:47 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_sprites(t_vars *vars)
{
	int		i;
	int		j;

	vars->map.sprites = 0;
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (vars->map.map[i][j] == '2')
				vars->map.sprites++;
			j++;
		}
		i++;
	}
	if (vars->map.sprites != 0)
	{
		vars->spr.mapx = (double*)malloc(sizeof(double) * vars->map.sprites);
		vars->spr.mapy = (double*)malloc(sizeof(double) * vars->map.sprites);
		vars->spr.dist = (double*)malloc(sizeof(double) * vars->map.sprites);
	}
}

void	set_sprites(t_vars *vars)
{
	int		i;
	int		j;
	int		x;

	x = 0;
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (vars->map.map[i][j] == '2')
			{
				vars->spr.mapx[x] = i + 0.5;
				vars->spr.mapy[x] = j + 0.5;
				vars->map.map[i][j] = '4';
				x++;
			}
			j++;
		}
		i++;
	}
}
