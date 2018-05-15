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
# define THREADS        4
# define OFF_X			0
# define OFF_Y			0
# define ROT_DEGREES	5
# define MV_PIXELS		5

/*
** ------ STRUCTS ------
*/
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
	int			start;
	int			end;
	int			color;
	int			max_iter;
	int			shft;
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
void			put_img_vector(t_canvas *c, int x, int y);

/*
** mutate.c
*/
void			switch_fractal(t_canvas *c, t_fractal f);
void			zoom(t_canvas *c,int direction, double value);
void			move(t_canvas *c, double *direction, double value);


/*
** fractals.c
*/
void			*mandelbrot_set(void* param);
void			*julia_set(void* param);


#endif