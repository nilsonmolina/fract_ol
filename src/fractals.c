/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/15 15:52:49 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*mandelbrot_set(void *param)
{
	t_canvas	*c;
	t_vars		v;

	c = (t_canvas *)param;
	v.y = c->start;
	while (v.y < c->end)
	{
		v.x = 0;
		while (v.x < c->img.width)
		{
			v.pr = 1.5 * (v.x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			v.pi = (v.y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			v.new_re = 0;
			v.new_im = 0;
			v.old_re = 0;
			v.old_im = 0;
			v.i = 0;
			while (v.i < c->max_iter)
			{
				v.old_re = v.new_re;
				v.old_im = v.new_im;
				v.new_re = v.old_re * v.old_re - v.old_im * v.old_im + v.pr;
				if (c->fractal == mandelbrot)
					v.new_im = 2 * v.old_re * v.old_im + v.pi;
				else if (c->fractal == burning_ship)
					v.new_im = 2 * fabs(v.old_re * v.old_im) + v.pi;
				if ((v.new_re * v.new_re + v.new_im * v.new_im) > 4)
					break ;
				v.i++;
			}
			if (v.i < c->max_iter)
				put_img_vector(c, v.x, v.y, v.i);
			v.x++;
		}
		v.y++;
	}
	return (NULL);
}

void	*julia_set(void *param)
{
	t_canvas	*c;
	t_vars		v;

	c = (t_canvas *)param;
	v.y = c->start;
	while (v.y < c->end)
	{
		v.x = 0;
		while (v.x < c->img.width)
		{
			v.new_re = 1.5 * (v.x - 400) / (0.5 * c->zoom * c->img.width) + c->offset_x;
			v.new_im = (v.y - 300) / (0.5 * c->zoom * c->img.height) + c->offset_y;
			v.i = 0;
			while (v.i < c->max_iter)
			{
				v.old_re = v.new_re;
				v.old_im = v.new_im;
				if (c->fractal == swirlia)
				{
					v.new_re = v.old_re * v.old_re - v.old_im * v.old_im + (-0.7 * 291 / 300);
					v.new_im = 2 * v.old_re * v.old_im + (0.27015 * 400 / 300);
				}
				else if (c->fractal == julia)
				{
					v.new_re = v.old_re * v.old_re - v.old_im * v.old_im + (-0.7 * c->mouse_x / 300);
					v.new_im = 2 * v.old_re * v.old_im + (0.27015 * c->mouse_y / 300);
				}
				if ((v.new_re * v.new_re + v.new_im * v.new_im) > 4)
					break ;
				v.i++;
			}
			if (v.i < c->max_iter)
				put_img_vector(c, v.x, v.y, v.i);
			v.x++;
		}
		v.y++;
	}
	return (NULL);
}
