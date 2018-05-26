/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:44:25 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/26 01:28:49 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_js_vars(t_canvas *c, t_vars *v)
{
	if (c->fractal == julia)
	{
		v->n_re = 1.5 * (v->x - 400) / (c->zoom * 140) + c->offset_x;
		v->n_im = (c->start - 300) / (c->zoom * 105) + c->offset_y;
	}
	else
	{
		v->n_re = 1.5 * (v->x - 400) / (c->zoom * 280) + c->offset_x;
		v->n_im = (c->start - 300) / (c->zoom * 210) + c->offset_y;
	}
	v->i = -1;
}

void	more_fractals(t_canvas *c, t_vars *v)
{
	if (c->fractal == julia_shield)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 0 / 300) /
			(v->o_re * v->o_re - v->o_im * v->o_im);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * 2 / 300) /
			(2 * v->o_re * v->o_im);
	}
	else if (c->fractal == dulia)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 100 / 300);
		v->n_im = fabs(2 * v->o_re * v->o_im) + (0.27015 * 180 / 300);
	}
	else if (c->fractal == dulia2)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 10 / 300);
		v->n_im = 2 * fabs(v->o_re * v->o_im) + (0.27015 * 313 / 300);
	}
}

void	set_new(t_canvas *c, t_vars *v)
{
	v->o_re = v->n_re;
	v->o_im = v->n_im;
	if (c->fractal == julia)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im +
			(-0.7 * c->mouse_x / 300);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * c->mouse_y / 300);
	}
	else if (c->fractal == swirlia)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 352 / 300);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * 180 / 300);
	}
	else if (c->fractal == swirlia2)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 288 / 300);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * 402 / 300);
	}
	else
		more_fractals(c, v);
}

void	*julia_set(void *param)
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
			set_js_vars(c, v);
			while (++v->i < c->max_iter)
			{
				set_new(c, v);
				if ((v->n_re * v->n_re + v->n_im * v->n_im) > 4)
					break ;
			}
			if (v->i < c->max_iter)
				put_img_vector(c, v->x, c->start, v->i);
		}
		c->start++;
	}
	free(v);
	return (NULL);
}
