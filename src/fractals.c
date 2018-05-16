/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/16 01:21:26 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*mandelbrot_set(void *param)
{
	t_canvas	*c;

	c = (t_canvas *)param;
	c->v.y = c->start;
	while (c->v.y < c->end)
	{
		c->v.x = 0;
		while (c->v.x < c->img.width)
		{
			c->v.pr = 1.5 * (c->v.x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			c->v.pi = (c->v.y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			c->v.new_re = 0;
			c->v.new_im = 0;
			c->v.old_re = 0;
			c->v.old_im = 0;
			c->v.i = 0;
			while (c->v.i < c->max_iter)
			{
				c->v.old_re = c->v.new_re;
				c->v.old_im = c->v.new_im;
				c->v.new_re = c->v.old_re * c->v.old_re - c->v.old_im * c->v.old_im + c->v.pr;
				if (c->fractal == mandelbrot)
					c->v.new_im = 2 * c->v.old_re * c->v.old_im + c->v.pi;
				else if (c->fractal == burning_ship)
					c->v.new_im = 2 * fabs(c->v.old_re * c->v.old_im) + c->v.pi;
				if ((c->v.new_re * c->v.new_re + c->v.new_im * c->v.new_im) > 4)
					break ;
				c->v.i++;
			}
			if (c->v.i < c->max_iter)
				put_img_vector(c, c->v.x, c->v.y, c->v.i);
			c->v.x++;
		}
		c->v.y++;
	}
	return (NULL);	
}

void	*julia_set(void *param)
{
	t_canvas	*c;
	t_vars		*v;

	v = malloc(sizeof(t_vars));
	c = (t_canvas *)param;
	c->v.y = c->start;
	while (c->v.y < c->end)
	{
		c->v.x = 0;
		while (c->v.x < c->img.width)
		{
			c->v.new_re = 1.5 * (c->v.x - 400) / (0.5 * c->zoom * c->img.width) + c->offset_x;
			c->v.new_im = (c->v.y - 300) / (0.5 * c->zoom * c->img.height) + c->offset_y;
			c->v.i = 0;
			while (c->v.i < c->max_iter)
			{
				c->v.old_re = c->v.new_re;
				c->v.old_im = c->v.new_im;
				if (c->fractal == swirlia)
				{
					c->v.new_re = c->v.old_re * c->v.old_re - c->v.old_im * c->v.old_im + (-0.7 * 291 / 300);
					c->v.new_im = 2 * c->v.old_re * c->v.old_im + (0.27015 * 400 / 300);
				}
				else if (c->fractal == julia)
				{
					c->v.new_re = c->v.old_re * c->v.old_re - c->v.old_im * c->v.old_im + (-0.7 * c->mouse_x / 300);
					c->v.new_im = 2 * c->v.old_re * c->v.old_im + (0.27015 * c->mouse_y / 300);
				}
				if ((c->v.new_re * c->v.new_re + c->v.new_im * c->v.new_im) > 4)
					break ;
				c->v.i++;
			}
			if (c->v.i < c->max_iter)
				put_img_vector(c, c->v.x, c->v.y, c->v.i);
			c->v.x++;
		}
		c->v.y++;
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
		c->color = 5;
		c->fractal = f;
		draw(c);
	}
}
