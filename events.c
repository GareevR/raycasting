/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:24:20 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 20:27:58 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				events_release(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->evt.forward = 0;
	if (keycode == 123)
		vars->evt.left = 0;
	if (keycode == 1)
		vars->evt.back = 0;
	if (keycode == 124)
		vars->evt.right = 0;
	if (keycode == 2)
		vars->evt.mvright = 0;
	if (keycode == 0)
		vars->evt.mvleft = 0;
	return (0);
}

int				events_press(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->evt.forward = 1;
	if (keycode == 123)
		vars->evt.left = 1;
	if (keycode == 1)
		vars->evt.back = 1;
	if (keycode == 124)
		vars->evt.right = 1;
	if (keycode == 2)
		vars->evt.mvright = 1;
	if (keycode == 0)
		vars->evt.mvleft = 1;
	if (keycode == 53)
		vars->evt.escape = 1;
	return (0);
}

int				closex(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}
