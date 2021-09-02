/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flr_ceil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:36:34 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 21:29:39 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor_clr(t_vars *vars, char **str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	r = 0;
	while (str[r])
		r++;
	if (r != 2)
		exit(error_return("invalid FLOOR color"));
	check_rgb(str[1]);
	rgb = ft_split(str[1], ',');
	check_values(rgb, "Invalid FLOOR color");
	create_rgb(&r, &g, &b, rgb);
	if (vars->flags.flr == 0 || vars->map.iter != 0)
	{
		vars->floor_clr = (r << 16 | g << 8 | b);
		vars->flags.flr = 1;
	}
	else
		exit(error_return("excess FLOOR color"));
	free_arr(rgb);
}

void	set_ceil_clr(t_vars *vars, char **str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	r = 0;
	while (str[r])
		r++;
	if (r != 2)
		exit(error_return("invalid CEIL color"));
	check_rgb(str[1]);
	rgb = ft_split(str[1], ',');
	check_values(rgb, "Invalid CEIL color");
	create_rgb(&r, &g, &b, rgb);
	if (vars->flags.ceil == 0 || vars->map.iter != 0)
	{
		vars->ceil_clr = (r << 16 | g << 8 | b);
		vars->flags.ceil = 1;
	}
	else
		exit(error_return("excess CEIL color"));
	free_arr(rgb);
}

void	create_rgb(int *r, int *g, int *b, char **rgb)
{
	int		n;
	int		x;

	x = 0;
	n = 0;
	while (rgb[n])
		n++;
	if (n != 3)
		exit(error_return("invalid FLOOR or CEIL color"));
	while (x < 3)
	{
		while (rgb[x][n] != '\0')
		{
			if (rgb[x][n] > '9' || rgb[x][n] < '0')
				exit(error_return("invalid FLOOR or CEIL color"));
			n++;
		}
		x++;
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *g < 0 || *b < 0 ||
		*r > 255 || *g > 255 || *b > 255)
		exit(error_return("invalid FLOOR or CEIL color"));
}

void	check_rgb(char *str)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			k++;
		i++;
	}
	if (k != 2)
		exit(error_return("invalid FLOOR or CEIL color"));
}
