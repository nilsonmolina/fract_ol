/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 05:45:36 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/24 11:28:00 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_ms_vars(t_canvas *c, t_vars *v)
{
	v->pr = 1.5 * (v->x - c->img->width / 2) /
		(0.25 * c->zoom * c->img->width) + c->offset_x;
	v->pi = (c->start - c->img->height / 2) /
		(0.25 * c->zoom * c->img->height) + c->offset_y;
	v->n_re = 0;
	v->n_im = 0;
	v->o_re = 0;
	v->o_im = 0;
	v->i = -1;
}

void	set_fractal(t_canvas *c, t_vars *v)
{
	v->o_re = v->n_re;
	v->o_im = v->n_im;
	v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + v->pr;
	if (c->fractal == mandelbrot)
		v->n_im = 2 * v->o_re * v->o_im + v->pi;
	else if (c->fractal == burning_ship)
		v->n_im = 2 * fabs(v->o_re * v->o_im) + v->pi;
}

void	*mandelbrot_set(void *param)
{
	t_canvas	*c;
	t_vars		*v;

	c = (t_canvas *)param;
	v = malloc(sizeof(t_vars));
	while (c->start < c->end)
	{
		v->x = -1;
		while (++v->x < c->img->width)
		{
			set_ms_vars(c, v);
			while (++v->i < c->max_iter)
			{
				set_fractal(c, v);
				if ((v->n_re * v->n_re + v->n_im * v->n_im) > 4)
					break ;
				v->i++;
			}
			(v->i < c->max_iter) ? put_img_vector(c, v->x, c->start, v->i) : 0;
		}
		c->start++;
	}
	free(v);
	return (NULL);
}
