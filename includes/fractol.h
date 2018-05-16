/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:51:48 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/15 23:53:32 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** ------ LIBRARIES ------
*/
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

# include <stdio.h> // remove this before turning in

/*
** ------ VARIABLES ------
*/
# define WIN_WIDTH		800
# define WIN_HEIGHT		600
# define OFF_X			0
# define OFF_Y			0
# define ROT_DEGREES	5
# define MV_PIXELS		5
# define WH				0xFFFFFF
# define GREY			0xAAAAAA
# define VARS double pr, pi, new_re, new_im, old_re, old_im; int x, y, i;

/*
** ------ STRUCTS ------
*/
typedef struct	s_vars
{
	double		pr;
	double		pi;
	double		new_re;
	double		new_im;
	double		old_re;
	double		old_im;
	int			x;
	int			y;
	int			i;
}				t_vars;

typedef enum	e_fractal
{
	mandelbrot = 1,
	burning_ship,
	julia,
	swirlia
}				t_fractal;

typedef struct	s_img
{
	int			bpp;
	int			sl;
	int			e;
	void		*ptr;
	int			*data;
	int			width;
	int			height;
}				t_img;

typedef struct	s_canvas
{
	void		*mlx;
	void		*window;
	t_img		img;
	t_fractal	fractal;
	t_vars		v;
	int			start;
	int			end;
	int			color;
	int			max_iter;
	int			shft;
	int			threads;
	double		zoom;
	double		offset_x;
	double		offset_y;
	double		mouse_x;
	double		mouse_y;
}				t_canvas;

/*
** ------ PUBLIC FUNCTIONS ------
** main.c
*/
void			usage();
void			check_error(int err, char *msg);

/*
** events.c
*/
int				key_up(int key, t_canvas *c);
int				key_hold(int key, t_canvas *c);
int				mouse_motion(int x, int y, t_canvas *c);
int				mouse_click(int mouse, int x, int y, t_canvas *c);

/*
** render.c
*/
void			draw(t_canvas *c);
void			put_img_vector(t_canvas *c, int x, int y, int color);
void			change_threads(t_canvas *c);

/*
** mutate.c
*/
void			zoom(t_canvas *c, double value, int x, int y);
void			move(t_canvas *c, double *direction, double value);
void			change_iter(t_canvas *c, int value);
void			change_color(t_canvas *c);

/*
** fractals.c
*/
void			*mandelbrot_set(void *param);
void			*julia_set(void *param);
void			switch_fractal(t_canvas *c, t_fractal f);

#endif
