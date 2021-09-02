/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frariel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:15:38 by frariel           #+#    #+#             */
/*   Updated: 2021/03/04 22:22:00 by frariel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

typedef	struct	s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			lnlen;
	int			endian;
}				t_data;

typedef	struct	s_text
{
	void		*img[5];
	char		*addr[5];
	int			bpp[5];
	int			lnlen[5];
	int			endian[5];
	int			width[5];
	int			height[5];
	int			num;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		pos;
}				t_tex;

typedef struct	s_plr
{
	double		posx;
	double		posy;
	double		movespeed;
	double		rotspeed;
	double		dirx;
	double		diry;
	double		camerax;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	char		nwse;
}				t_plr;

typedef struct	s_ray
{
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			hit;
	int			side;
	double		planex;
	double		planey;
	double		raydirx;
	double		raydiry;
}				t_ray;

typedef struct	s_scn
{
	int		width;
	int		height;
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_scn;

typedef	struct	s_evt
{
	int		right;
	int		mvright;
	int		left;
	int		forward;
	int		back;
	int		mvleft;
	int		escape;
}				t_evt;

typedef struct	s_spr
{
	double	*mapx;
	double	*mapy;
	double	*dist;
	int		order;
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		screenx;
	int		height;
	int		width;
	int		drawstartx;
	int		drawstarty;
	int		drawendx;
	int		drawendy;
	int		texx;
	int		texy;
	int		d;
}				t_spr;

typedef struct	s_flags
{
	int		res;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		spr;
	int		flr;
	int		ceil;
	int		save;
}				t_flags;

typedef struct	s_info
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*spr_path;
}				t_info;

typedef	struct	s_map
{
	char	**map;
	int		height;
	int		width;
	int		iter;
	int		sprites;
}				t_map;

typedef struct	s_vars
{
	t_map			map;
	t_data			img;
	t_plr			plr;
	t_ray			ray;
	t_scn			screen;
	t_evt			evt;
	t_tex			tex;
	t_spr			spr;
	t_flags			flags;
	t_info			data;
	unsigned int	color;
	void			*mlx;
	void			*win;
	unsigned int	floor_clr;
	unsigned int	ceil_clr;
	double			*zbuffer;
	int				argc;
}				t_vars;

typedef struct	s_bmp_h
{
	char		b;
	char		m;
	int			size;
	int			reserve;
	int			offset;
}				t_bmp_h;

typedef struct	s_bmp_i
{
	int			size;
	int			width;
	int			height;
	short		planes;
	short		bpp;
	int			compress;
	int			img_size;
	int			x_ppm;
	int			y_ppm;
	int			colors;
	int			colors_size;
}				t_bmp_i;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				drawsquare(int keycode, t_vars *vars);
void			drawmap(t_vars *vars);
int				process(t_vars *vars);
void			drawplr(t_vars *vars);
double			my_abs(double num);
void			calculate(t_vars *vars);

int				events_press(int keycode, t_vars *vars);
int				events_release(int keycode, t_vars *vars);
int				closex(t_vars *vars);
void			mv_left(t_vars *vars, double olddirx, double oldplanex);
void			mv_right(t_vars *vars, double olddirx, double oldplanex);
void			mv_forward_back(t_vars *vars);
void			rotate_camera(t_vars *vars, double olddirx, double oldplanex);

unsigned int	ft_color(t_vars *vars);

void			find_delta_dist(t_vars *vars, int x);
void			find_perp_n_draw(t_vars *vars);
void			calc_side_dist(t_vars *vars);
void			texture_calc(t_vars *vars);
void			draw_sky_floor(t_vars *vars, int x);
void			draw_tex_walls(t_vars *vars, int x);
void			hit_check(t_vars *vars);
void			sprite_casting(t_vars *vars);
unsigned int	ft_spr_color(t_vars *vars);
void			sortsprites(t_vars *vars, int amount);
int				tex_choose(t_vars *vars);

void			parse_map(int fd, t_vars *vars);
void			parser(char **argv, t_vars *vars);
int				check_info(t_vars *vars);
void			parse_string(t_vars *vars, char *line, int *num);
void			set_resolution(t_vars *vars, char **str);
void			set_tex_no(t_vars *vars, char **str);
void			set_tex_so(t_vars *vars, char **str);
void			set_tex_we(t_vars *vars, char **str);
void			set_tex_ea(t_vars *vars, char **str);
void			set_tex_spr(t_vars *vars, char **str);
void			set_floor_clr(t_vars *vars, char **str);
void			set_ceil_clr(t_vars *vars, char **str);
void			set_player_nw(t_vars *vars);
void			set_player_se(t_vars *vars);
void			create_rgb(int *r, int *g, int *b, char **rgb);
void			free_arr(char	**arr);
void			copy_line(t_vars *vars, char *line, int i);
void			fill_2d_map(int fd, t_vars *vars, char *line);
void			find_mapscale(int fd, t_vars *vars, char *line);
void			check_map(t_vars *vars);
void			check_rgb(char *str);
void			check_player(t_vars *vars);
void			check_walls(t_vars *vars);
void			check_srnd(t_vars *vars, int i, int j);
void			check_grid(t_vars *vars);
void			count_sprites(t_vars *vars);
void			set_sprites(t_vars *vars);
void			parse_all(t_vars *vars, char **argv);
int				error_return(char *str);
void			check_argv(char **argv, t_vars *vars);
void			check_xpm(t_vars *vars);
void			check_cub(t_vars *vars, char *str, int k);
void			set_player(t_vars *vars);
void			check_values(char **arr, char *str);
void			check_resolution(t_vars *vars);
void			set_files(t_vars *vars);
void			nullify_values(t_vars *vars);

void			get_screen(t_vars *vars);
void			fill_bmp(t_vars *vars, t_bmp_h *head, t_bmp_i *inf);

#endif
