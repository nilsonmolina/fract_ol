/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/17 14:06:23 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    *mandelbrot_set(void* param)
{
	t_canvas	*c;
    t_vars		*v;

	c = (t_canvas *)param;
	v = malloc(sizeof(t_vars));
	v->y = c->start;
	while (v->y < c->end)
	{
		v->x = 0;
		while (v->x < c->img.width)
		{
			v->pr = 1.5 * (v->x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			v->pi = (v->y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			v->n_re = 0;
			v->n_im = 0;
			v->o_re = 0;
			v->o_im = 0;
			v->i = 0;
			while (v->i < c->max_iter)
			{
				v->o_re = v->n_re;
				v->o_im = v->n_im;
				v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + v->pr;
				if (c->fractal == mandelbrot)
					v->n_im = 2 * v->o_re * v->o_im + v->pi;
				else if (c->fractal == burning_ship)
					v->n_im = 2 * fabs(v->o_re * v->o_im) + v->pi;
				if ((v->n_re * v->n_re + v->n_im * v->n_im) > 4)
					break;
				v->i++;
			}
			if (v->i < c->max_iter)
				put_img_vector(c, v->x, v->y, v->i);
			v->x++;
		}
		v->y++;
	}
	return(NULL);
}

void*	julia_set(void *param)
{
	t_canvas *c = (t_canvas *)param;
    VARS;
	pi = 0;
	pr = 0;

	y = c->start;	
	while (y < c->end)
	{
		x = 0;
		while (x < c->img.width)
		{
			n_re = 1.5 * (x - 400) / (0.5 * c->zoom * c->img.width) + c->offset_x;
			n_im = (y - 300) / (0.5 * c->zoom * c->img.height) + c->offset_y;
			i = 0;
			while (i < c->max_iter)
			{
				o_re = n_re;
				o_im = n_im;
				if (c->fractal == swirlia)
				{
					n_re = o_re * o_re - o_im * o_im + (-0.7 * 291 / 300);
					n_im = 2 * o_re * o_im + (0.27015 * 400 / 300);
				}
				else if (c->fractal == julia)
				{
					n_re = o_re * o_re - o_im * o_im + (-0.7 * c->mouse_x / 300);
					n_im = 2 * o_re * o_im + (0.27015 * c->mouse_y / 300);
				}
				if ((n_re * n_re + n_im * n_im) > 4)
					break;
				i++;
			}
			if (i < c->max_iter)
				put_img_vector(c, x, y, i);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	switch_fractal(t_canvas *c, t_fractal f)
{
	if (c->zoom != 1 || c->max_iter != 50 ||
		c->offset_x != 0 || c->offset_y != 0 ||
		c->fractal != f || c->color != 1)
	{
		c->zoom = 1;
		c->max_iter = 50;
		c->offset_x = 0;
		c->offset_y = 0;
		c->color = 10;
		c->fractal = f;
		draw(c);
	}
}