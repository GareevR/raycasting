/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:22:06 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 20:40:54 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_sky_floor(t_vars *vars, int x)
{
	int				sky;
	unsigned int	color;
	int				k;

	sky = 0;
	color = vars->ceil_clr;
	k = 0;
	while (sky < vars->screen.drawstart)
	{
		my_mlx_pixel_put(&vars->img, x, sky, color);
		sky++;
		k++;
		if (k % 10 == 0)
			color--;
	}
	sky = vars->screen.drawend;
	while (sky < vars->screen.height)
	{
		my_mlx_pixel_put(&vars->img, x, sky, vars->floor_clr);
		sky++;
	}
}

void			draw_tex_walls(t_vars *vars, int x)
{
	int		y;

	y = vars->screen.drawstart;
	while (y < vars->screen.drawend)
	{
		vars->tex.texy = (int)vars->tex.pos & \
			(vars->tex.height[vars->tex.num] - 1);
		vars->tex.pos += vars->tex.step;
		vars->color = ft_color(vars);
		my_mlx_pixel_put(&vars->img, x, y, vars->color);
		y++;
	}
}

unsigned int	ft_color(t_vars *vars)
{
	char			*addr;
	unsigned int	color;
	int				i;

	i = vars->tex.num;
	addr = vars->tex.addr[i] + (vars->tex.texy * vars->tex.lnlen[i] +
								vars->tex.texx * (vars->tex.bpp[i] / 8));
	color = *(unsigned int*)addr;
	if ((color & 0x00FFFFFF) == 0)
		color = 0x000000;
	return (color);
}

unsigned int	ft_spr_color(t_vars *vars)
{
	char			*addr;
	unsigned int	color;

	color = 0;
	addr = vars->tex.addr[4] + (vars->spr.texy * vars->tex.lnlen[4] +
								vars->spr.texx * (vars->tex.bpp[4] / 8));
	color = *(unsigned int*)addr;
	return (color);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->lnlen + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
