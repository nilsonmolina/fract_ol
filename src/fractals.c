/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/21 14:50:39 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    *mandelbrot_set(void* param)
{
	t_canvas	*c;
	VARS;

	c = (t_canvas *)param;
	y = c->start;
	while (y < c->end)
	{
		x = 0;
		while (x < c->img.width)
		{
			pr = 1.5 * (x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			pi = (y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			n_re = 0;
			n_im = 0;
			o_re = 0;
			o_im = 0;
			i = 0;
			while (i < c->max_iter)
			{
				o_re = n_re;
				o_im = n_im;
				n_re = o_re * o_re - o_im * o_im + pr;
				if (c->fractal == mandelbrot)
					n_im = 2 * o_re * o_im + pi;
				else if (c->fractal == burning_ship)
					n_im = 2 * fabs(o_re * o_im) + pi;
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
