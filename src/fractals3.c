/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/16 18:31:21 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    *mandelbrot_set(void* param)
{
	t_canvas *c = (t_canvas *)param;
    VARS;

	y = c->start;
	while (y < c->end)
	{
		x = 0;
		while (x < c->img.width)
		{
			pr = 1.5 *(x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			pi = (y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			new_re = 0;
			new_im = 0;
			old_re = 0;
			old_im = 0;
			i = 0;
			while (i < c->max_iter)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + pr;
				if (c->fractal == mandelbrot)
					new_im = 2 * old_re * old_im + pi;
				else if (c->fractal == burning_ship)
					new_im = 2 * fabs(old_re * old_im) + pi;
				if ((new_re * new_re + new_im * new_im) > 4)
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
			new_re = 1.5 * (x - 400) / (0.5 * c->zoom * c->img.width) + c->offset_x;
			new_im = (y - 300) / (0.5 * c->zoom * c->img.height) + c->offset_y;
			i = 0;
			while (i < c->max_iter)
			{
				old_re = new_re;
				old_im = new_im;
				if (c->fractal == swirlia)
				{
					new_re = old_re * old_re - old_im * old_im + (-0.7 * 291 / 300);
					new_im = 2 * old_re * old_im + (0.27015 * 400 / 300);
				}
				else if (c->fractal == julia)
				{
					new_re = old_re * old_re - old_im * old_im + (-0.7 * c->mouse_x / 300);
					new_im = 2 * old_re * old_im + (0.27015 * c->mouse_y / 300);
				}
				if ((new_re * new_re + new_im * new_im) > 4)
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