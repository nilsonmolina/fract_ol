#ifndef FRACTOL_H
# define FRACTOL_H

/*
** ------ LIBRARIES ------
*/
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

#include <stdio.h> // remove this before turning in

/*
** ------ VARIABLES ------
*/
# define WIN_WIDTH		1280
# define WIN_HEIGHT		720
# define THREADS        13
# define OFF_X			0
# define OFF_Y			0
# define ROT_DEGREES	5
# define MV_PIXELS		5

/*
** ------ STRUCTS ------
*/
typedef struct	s_img
{
	int			bpp;
	int			sl;
	int			e;
	void		*img;
	int			*data;
	int			width;
	int			height;
}				t_img;

typedef struct	s_canvas
{
	void		*mlx;
	void		*window;
	t_img		img;
	int			shft;
	int			mode;
	int			color_on;
}				t_canvas;

/*
** ------ PUBLIC FUNCTIONS ------
** main.c
*/
void			usage();

/*
** events.c
*/


/*
** fractals.c
*/


#endif