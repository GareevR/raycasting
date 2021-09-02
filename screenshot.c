/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:38:00 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:10:53 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_bmp(t_vars *vars, t_bmp_h *head, t_bmp_i *inf)
{
	int		fd;

	fd = open("cub.bmp", O_RDWR | O_CREAT, 0755);
	if (fd < 0)
		exit(error_return("Screenshot creation failed"));
	write(fd, &(head->b), 1);
	write(fd, &(head->m), 1);
	write(fd, &(head->size), 4);
	write(fd, &(head->reserve), 4);
	write(fd, &(head->offset), 4);
	write(fd, &(inf->size), 4);
	write(fd, &(inf->width), 4);
	write(fd, &(inf->height), 4);
	write(fd, &(inf->planes), 2);
	write(fd, &(inf->bpp), 2);
	write(fd, &(inf->compress), 4);
	write(fd, &(inf->img_size), 4);
	write(fd, &(inf->x_ppm), 4);
	write(fd, &(inf->y_ppm), 4);
	write(fd, &(inf->colors), 4);
	write(fd, &(inf->colors_size), 4);
	write(fd, vars->img.addr, inf->img_size * inf->bpp / 8);
	close(fd);
}

void	get_screen(t_vars *vars)
{
	t_bmp_h		head;
	t_bmp_i		inf;

	head.b = 'B';
	head.m = 'M';
	head.reserve = 0;
	head.size = 40 + 14 + vars->img.bpp /
		8 * vars->screen.width * vars->screen.height;
	head.offset = 40 + 14;
	inf.size = 40;
	inf.width = vars->screen.width;
	inf.height = -vars->screen.height;
	inf.planes = 1;
	inf.bpp = (short)vars->img.bpp;
	inf.compress = 0;
	inf.img_size = vars->screen.width * vars->screen.height;
	inf.x_ppm = 1000;
	inf.y_ppm = 1000;
	inf.colors = 0;
	inf.colors_size = 0;
	fill_bmp(vars, &head, &inf);
	exit(0);
}
