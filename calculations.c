/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:25:17 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 20:26:41 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			calc_side_dist(t_vars *vars)
{
	if (vars->ray.raydirx < 0)
	{
		vars->plr.stepx = -1;
		vars->ray.sidedistx = (vars->plr.posx - vars->plr.mapx) \
		* vars->ray.deltadistx;
	}
	else
	{
		vars->plr.stepx = 1;
		vars->ray.sidedistx = (vars->plr.mapx + 1.0 - vars->plr.posx) \
		* vars->ray.deltadistx;
	}
	if (vars->ray.raydiry < 0)
	{
		vars->plr.stepy = -1;
		vars->ray.sidedisty = (vars->plr.posy - vars->plr.mapy) * \
		vars->ray.deltadisty;
	}
	else
	{
		vars->plr.stepy = 1;
		vars->ray.sidedisty = (vars->plr.mapy + 1.0 - vars->plr.posy) * \
		vars->ray.deltadisty;
	}
}

void			hit_check(t_vars *vars)
{
	while (vars->ray.hit == 0)
	{
		if (vars->ray.sidedistx < vars->ray.sidedisty)
		{
			vars->ray.sidedistx += vars->ray.deltadistx;
			vars->plr.mapx += vars->plr.stepx;
			vars->ray.side = 0;
		}
		else
		{
			vars->ray.sidedisty += vars->ray.deltadisty;
			vars->plr.mapy += vars->plr.stepy;
			vars->ray.side = 1;
		}
		if (vars->map.map[vars->plr.mapx][vars->plr.mapy] != '0' &&
			vars->map.map[vars->plr.mapx][vars->plr.mapy] != '4')
			vars->ray.hit = 1;
	}
}

void			find_delta_dist(t_vars *vars, int x)
{
	vars->plr.camerax = 2 * x / (double)(vars->screen.width) - 1;
	vars->ray.raydirx = vars->plr.dirx + vars->ray.planex * vars->plr.camerax;
	vars->ray.raydiry = vars->plr.diry + vars->ray.planey * vars->plr.camerax;
	vars->plr.mapx = (int)vars->plr.posx;
	vars->plr.mapy = (int)vars->plr.posy;
	vars->ray.deltadistx = sqrt(1 + (vars->ray.raydiry * \
		vars->ray.raydiry) / (vars->ray.raydirx * vars->ray.raydirx));
	vars->ray.deltadisty = sqrt(1 + (vars->ray.raydirx * \
		vars->ray.raydirx) / (vars->ray.raydiry * vars->ray.raydiry));
	vars->ray.hit = 0;
}

void			find_perp_n_draw(t_vars *vars)
{
	if (vars->ray.side == 0)
		vars->ray.perpwalldist = (vars->plr.mapx - vars->plr.posx +
			(1 - vars->plr.stepx) / 2) / vars->ray.raydirx;
	else
		vars->ray.perpwalldist = (vars->plr.mapy - vars->plr.posy +
			(1 - vars->plr.stepy) / 2) / vars->ray.raydiry;
	vars->screen.lineheight = (int)(vars->screen.height /
		vars->ray.perpwalldist);
	vars->screen.drawstart = -vars->screen.lineheight / 2 +
		vars->screen.height / 2;
	if (vars->screen.drawstart < 0)
		vars->screen.drawstart = 0;
	vars->screen.drawend = vars->screen.lineheight / 2 +
		vars->screen.height / 2;
	if (vars->screen.drawend >= vars->screen.height)
		vars->screen.drawend = vars->screen.height - 1;
}

void			texture_calc(t_vars *vars)
{
	vars->tex.num = tex_choose(vars);
	if (vars->ray.side == 0)
		vars->tex.wallx = vars->plr.posy +
			vars->ray.perpwalldist * vars->ray.raydiry;
	else
		vars->tex.wallx = vars->plr.posx +
			vars->ray.perpwalldist * vars->ray.raydirx;
	vars->tex.wallx -= floor((vars->tex.wallx));
	vars->tex.texx = (int)(vars->tex.wallx *
		(double)(vars->tex.width[vars->tex.num]));
	if (vars->ray.side == 0 && vars->ray.raydirx > 0)
		vars->tex.texx = vars->tex.width[vars->tex.num] - vars->tex.texx - 1;
	if (vars->ray.side == 1 && vars->ray.raydiry < 0)
		vars->tex.texx = vars->tex.width[vars->tex.num] - vars->tex.texx - 1;
	vars->tex.step = 1.0 * vars->tex.height[vars->tex.num] /
		vars->screen.lineheight;
	vars->tex.pos = (vars->screen.drawstart - vars->screen.height
		/ 2 + vars->screen.lineheight / 2) * vars->tex.step;
}
