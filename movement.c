/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:19:49 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 17:42:59 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawplr(t_vars *vars)
{
	double		olddirx;
	double		oldplanex;

	olddirx = 0.0;
	oldplanex = 0.0;
	if (vars->evt.mvright == 1)
		mv_right(vars, olddirx, oldplanex);
	if (vars->evt.escape == 1)
		closex(vars);
	if (vars->evt.mvleft == 1)
		mv_left(vars, olddirx, oldplanex);
	mv_forward_back(vars);
	rotate_camera(vars, olddirx, oldplanex);
}

void	mv_left(t_vars *vars, double olddirx, double oldplanex)
{
	olddirx = vars->plr.dirx;
	vars->plr.dirx = vars->plr.dirx * cos(M_PI_2) - \
	vars->plr.diry * sin(M_PI_2);
	vars->plr.diry = olddirx * sin(M_PI_2) + vars->plr.diry * cos(M_PI_2);
	oldplanex = vars->ray.planex;
	vars->ray.planex = vars->ray.planex * cos(M_PI_2) - \
	vars->ray.planey * sin(M_PI_2);
	vars->ray.planey = oldplanex * sin(M_PI_2) + vars->ray.planey * cos(M_PI_2);
	if (vars->map.map[(int)(vars->plr.posx + vars->plr.dirx * \
	vars->plr.movespeed)][(int)vars->plr.posy] == '0')
		vars->plr.posx = vars->plr.posx + vars->plr.dirx * vars->plr.movespeed;
	if (vars->map.map[(int)vars->plr.posx][(int)(vars->plr.posy + \
	vars->plr.diry * vars->plr.movespeed)] == '0')
		vars->plr.posy = vars->plr.posy + vars->plr.diry * vars->plr.movespeed;
	olddirx = vars->plr.dirx;
	vars->plr.dirx = vars->plr.dirx * cos(-M_PI_2) - \
	vars->plr.diry * sin(-M_PI_2);
	vars->plr.diry = olddirx * sin(-M_PI_2) + vars->plr.diry * cos(-M_PI_2);
	oldplanex = vars->ray.planex;
	vars->ray.planex = vars->ray.planex * cos(-M_PI_2) - \
	vars->ray.planey * sin(-M_PI_2);
	vars->ray.planey = oldplanex * sin(-M_PI_2) + \
	vars->ray.planey * cos(-M_PI_2);
}

void	mv_right(t_vars *vars, double olddirx, double oldplanex)
{
	olddirx = vars->plr.dirx;
	vars->plr.dirx = vars->plr.dirx * cos(-M_PI_2) - \
	vars->plr.diry * sin(-M_PI_2);
	vars->plr.diry = olddirx * sin(-M_PI_2) + vars->plr.diry * cos(-M_PI_2);
	oldplanex = vars->ray.planex;
	vars->ray.planex = vars->ray.planex * cos(-M_PI_2) - \
	vars->ray.planey * sin(-M_PI_2);
	vars->ray.planey = oldplanex * sin(-M_PI_2) + \
	vars->ray.planey * cos(-M_PI_2);
	if (vars->map.map[(int)(vars->plr.posx + vars->plr.dirx
		* vars->plr.movespeed)][(int)vars->plr.posy] == '0')
		vars->plr.posx = vars->plr.posx + vars->plr.dirx * vars->plr.movespeed;
	if (vars->map.map[(int)vars->plr.posx]
		[(int)(vars->plr.posy + vars->plr.diry * vars->plr.movespeed)] == '0')
		vars->plr.posy = vars->plr.posy + vars->plr.diry * vars->plr.movespeed;
	olddirx = vars->plr.dirx;
	vars->plr.dirx = vars->plr.dirx * cos(M_PI_2) - \
	vars->plr.diry * sin(M_PI_2);
	vars->plr.diry = olddirx * sin(M_PI_2) + vars->plr.diry * cos(M_PI_2);
	oldplanex = vars->ray.planex;
	vars->ray.planex = vars->ray.planex * cos(M_PI_2) - \
	vars->ray.planey * sin(M_PI_2);
	vars->ray.planey = oldplanex * sin(M_PI_2) + vars->ray.planey * cos(M_PI_2);
}

void	mv_forward_back(t_vars *vars)
{
	if (vars->evt.forward == 1)
	{
		if (vars->map.map[(int)(vars->plr.posx +
			vars->plr.dirx * vars->plr.movespeed)][(int)vars->plr.posy] == '0')
			vars->plr.posx = vars->plr.posx + \
			vars->plr.dirx * vars->plr.movespeed;
		if (vars->map.map[(int)vars->plr.posx][(int)(vars->plr.posy +
			vars->plr.diry * vars->plr.movespeed)] == '0')
			vars->plr.posy = vars->plr.posy + \
			vars->plr.diry * vars->plr.movespeed;
	}
	if (vars->evt.back == 1)
	{
		if (vars->map.map[(int)(vars->plr.posx - \
			vars->plr.dirx * vars->plr.movespeed)][(int)vars->plr.posy] == '0')
			vars->plr.posx = vars->plr.posx - \
			vars->plr.dirx * vars->plr.movespeed;
		if (vars->map.map[(int)vars->plr.posx][(int)(vars->plr.posy - \
			vars->plr.diry * vars->plr.movespeed)] == '0')
			vars->plr.posy = vars->plr.posy - \
			vars->plr.diry * vars->plr.movespeed;
	}
}

void	rotate_camera(t_vars *vars, double olddirx, double oldplanex)
{
	olddirx = vars->plr.dirx;
	if (vars->evt.right == 1)
	{
		vars->plr.dirx = vars->plr.dirx * cos(-vars->plr.rotspeed) - \
		vars->plr.diry * sin(-vars->plr.rotspeed);
		vars->plr.diry = olddirx * sin(-vars->plr.rotspeed) + \
		vars->plr.diry * cos(-vars->plr.rotspeed);
		oldplanex = vars->ray.planex;
		vars->ray.planex = vars->ray.planex * cos(-vars->plr.rotspeed) - \
		vars->ray.planey * sin(-vars->plr.rotspeed);
		vars->ray.planey = oldplanex * sin(-vars->plr.rotspeed) + \
		vars->ray.planey * cos(-vars->plr.rotspeed);
	}
	if (vars->evt.left == 1)
	{
		vars->plr.dirx = vars->plr.dirx * cos(vars->plr.rotspeed) - \
		vars->plr.diry * sin(vars->plr.rotspeed);
		vars->plr.diry = olddirx * sin(vars->plr.rotspeed) + \
		vars->plr.diry * cos(vars->plr.rotspeed);
		oldplanex = vars->ray.planex;
		vars->ray.planex = vars->ray.planex * cos(vars->plr.rotspeed) - \
		vars->ray.planey * sin(vars->plr.rotspeed);
		vars->ray.planey = oldplanex * sin(vars->plr.rotspeed) + \
		vars->ray.planey * cos(vars->plr.rotspeed);
	}
}
