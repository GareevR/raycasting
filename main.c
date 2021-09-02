/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:50:01 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:10:35 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				tex_choose(t_vars *vars)
{
	if (vars->ray.side == 0)
	{
		if (vars->plr.stepx > 0)
			return (0);
		else
			return (3);
	}
	else
	{
		if (vars->plr.stepy > 0)
			return (2);
		else
			return (1);
	}
}

int				process(t_vars *vars)
{
	drawplr(vars);
	calculate(vars);
	if (vars->flags.save != 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	else
		get_screen(vars);
	return (0);
}

void			calculate(t_vars *vars)
{
	int		x;

	x = 0;
	while (x < vars->screen.width)
	{
		find_delta_dist(vars, x);
		calc_side_dist(vars);
		hit_check(vars);
		find_perp_n_draw(vars);
		texture_calc(vars);
		draw_sky_floor(vars, x);
		draw_tex_walls(vars, x);
		vars->zbuffer[x] = vars->ray.perpwalldist;
		x++;
	}
	sprite_casting(vars);
}

void			game(t_vars *vars)
{
	mlx_loop_hook(vars->mlx, process, vars);
	if (vars->flags.save != 1)
	{
		mlx_hook(vars->win, 2, 1L << 0, events_press, vars);
		mlx_hook(vars->win, 17, 1L << 2, closex, vars);
		mlx_hook(vars->win, 3, 1L << 1, events_release, vars);
	}
	mlx_loop(vars->mlx);
}

int				main(int argc, char **argv)
{
	t_vars	vars;

	vars.argc = argc;
	parse_all(&vars, argv);
	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx,
		vars.screen.width, vars.screen.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bpp, &vars.img.lnlen, &vars.img.endian);
	if (vars.flags.save != 1)
		vars.win = mlx_new_window(vars.mlx, vars.screen.width,
			vars.screen.height, "Cub3D");
	vars.plr.movespeed = 0.09;
	vars.plr.rotspeed = 0.08;
	set_files(&vars);
	game(&vars);
	return (0);
}
