/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:12 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/02 14:47:54 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    *mandelbrot_set(void* param)
{
	t_canvas *c = (t_canvas *)param;
	double pr, pi;
	double new_re, new_im, old_re, old_im;
	int y = c->start;
	while (y < c->end)
	{
		int x = 0;
		while (x < c->img.width)
		{
			pr = 1.5 *(x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
			pi = (y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
			new_re = 0;
			new_im = 0;
			old_re = 0;
			old_im = 0;
			int i = 0;
			while (i < c->max_iter)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + pr;
				if (c->fractal == mandelbrot)
					new_im = 2 * old_re * old_im + pi;
				if ((new_re * new_re + new_im * new_im) > 4)
					break;
				i++;
			}
			if (i < c->max_iter)
				put_img_vector(c, x, y);
			x++;
		}
		y++;
	}
	return(NULL);
}