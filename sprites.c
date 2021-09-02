/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:21:32 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 20:23:33 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			find_sprite_draw(t_vars *vars)
{
	vars->spr.height = abs((int)(vars->screen.height /
		vars->spr.transformy));
	vars->spr.drawstarty = -vars->spr.height / 2 + vars->screen.height / 2;
	if (vars->spr.drawstarty < 0)
		vars->spr.drawstarty = 0;
	vars->spr.drawendy = vars->spr.height / 2 + vars->screen.height / 2;
	if (vars->spr.drawendy >= vars->screen.height)
		vars->spr.drawendy = vars->screen.height - 1;
	vars->spr.width = abs((int)(vars->screen.height /
		vars->spr.transformy));
	vars->spr.drawstartx = -vars->spr.width / 2 + vars->spr.screenx;
	if (vars->spr.drawstartx < 0)
		vars->spr.drawstartx = 0;
	vars->spr.drawendx = vars->spr.width / 2 + vars->spr.screenx;
	if (vars->spr.drawendx >= vars->screen.width)
		vars->spr.drawendx = vars->screen.width - 1;
}

void			find_sprite_xy(t_vars *vars, int i)
{
	vars->spr.spritex = vars->spr.mapx[i] - vars->plr.posx;
	vars->spr.spritey = vars->spr.mapy[i] - vars->plr.posy;
	vars->spr.invdet = 1.0 / (vars->ray.planex * vars->plr.diry - \
		vars->plr.dirx * vars->ray.planey);
	vars->spr.transformx = vars->spr.invdet * (vars->plr.diry * \
		vars->spr.spritex - vars->plr.dirx * vars->spr.spritey);
	vars->spr.transformy = vars->spr.invdet * (-vars->ray.planey * \
		vars->spr.spritex + vars->ray.planex * vars->spr.spritey);
	vars->spr.screenx = (int)((vars->screen.width / 2) *
		(1 + vars->spr.transformx / vars->spr.transformy));
}

void			draw_sprite(t_vars *vars)
{
	int		stripe;
	int		y;

	stripe = vars->spr.drawstartx - 1;
	while (++stripe < vars->spr.drawendx)
	{
		vars->spr.texx = (int)(256 * (stripe - (-vars->spr.width / 2 +
			vars->spr.screenx)) * vars->tex.width[4] / vars->spr.width) / 256;
		if (vars->spr.transformy > 0 && stripe > 0 && stripe <
			vars->screen.width && vars->spr.transformy < vars->zbuffer[stripe])
		{
			y = vars->spr.drawstarty;
			while (y < vars->spr.drawendy)
			{
				vars->spr.d = y * 256 - vars->screen.height * 128 +
					vars->spr.height * 128;
				vars->spr.texy = ((vars->spr.d * vars->tex.height[4]) /
					vars->spr.height) / 256;
				vars->color = ft_spr_color(vars);
				if ((vars->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&vars->img, stripe, y, vars->color);
				y++;
			}
		}
	}
}

void			sprite_casting(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->map.sprites)
	{
		vars->spr.dist[i] = (vars->plr.posx - vars->spr.mapx[i]) *
			(vars->plr.posx - vars->spr.mapx[i]) + (vars->plr.posy -
				vars->spr.mapy[i]) * (vars->plr.posy - vars->spr.mapy[i]);
		i++;
	}
	sortsprites(vars, vars->map.sprites);
	i = 0;
	while (i < vars->map.sprites)
	{
		find_sprite_xy(vars, i);
		find_sprite_draw(vars);
		draw_sprite(vars);
		i++;
	}
}

void			sortsprites(t_vars *vars, int amount)
{
	int		i;
	double	mapx;
	double	mapy;
	double	tmp;

	i = amount - 1;
	while (i > 0)
	{
		if (vars->spr.dist[i] > vars->spr.dist[i - 1])
		{
			tmp = vars->spr.dist[i];
			mapx = vars->spr.mapx[i];
			mapy = vars->spr.mapy[i];
			vars->spr.dist[i] = vars->spr.dist[i - 1];
			vars->spr.mapx[i] = vars->spr.mapx[i - 1];
			vars->spr.mapy[i] = vars->spr.mapy[i - 1];
			vars->spr.dist[i - 1] = tmp;
			vars->spr.mapx[i - 1] = mapx;
			vars->spr.mapy[i - 1] = mapy;
			i = amount - 1;
			continue ;
		}
		i--;
	}
}
