/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:44:25 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/22 22:43:32 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_js_vars(t_canvas *c, t_vars *v)
{
	// v->n_re = 1.5 * (v->x - 400) /
	// 	(0.5 * c->zoom * c->img.width) + c->offset_x;
	// v->n_im = (c->start - 300) /
	// 	(0.5 * c->zoom * c->img.height) + c->offset_y;
	// v->i = -1;
	if (c->fractal == julia)
	{
		v->n_re = 1.5 * (v->x - 400) / (c->zoom * 160) + c->offset_x;
		v->n_im = (c->start - 300) / (c->zoom * 100) + c->offset_y;
	}
	else
	{
		v->n_re = 1.5 * (v->x - 400) / (c->zoom * 280) + c->offset_x;
		v->n_im = (c->start - 300) / (c->zoom * 210) + c->offset_y;
	}
	v->i = -1;
}


			// c[0] = 1.5 * (x - 640) / (160 * map->zoom) + map->offset_x;
			// c[1] = (mlx->start - 400) / (100 * map->zoom) + map->offset_y;
			// i = -1;
			// while (++i < map->max_iter)
			// {
			// 	c[2] = c[0];
			// 	c[3] = c[1];
			// 	c[0] = c[2] * c[2] - c[3] * c[3] + (-0.7 * mlx->mouse_x / 300);
			// 	map->fractol == 4 ? (c[1] = fabs(2 * c[2] *
			// 		c[3]) + (0.27015 * mlx->mouse_y / 300)) : (c[1] = 2
			// 		* c[2] * c[3] + (0.27015 * mlx->mouse_y / 300));
			// 	if ((c[0] * c[0] + c[1] * c[1]) > 4)
			// 		break ;
			// }
			// (i < map->max_iter) ? put_pixel(mlx, x, mlx->start, 265 * i) : 0;

void	set_new(t_canvas *c, t_vars *v)
{
	v->o_re = v->n_re;
	v->o_im = v->n_im;
	if (c->fractal == swirlia)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + (-0.7 * 291 / 300);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * 400 / 300);
	}
	else if (c->fractal == julia)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im +
			(-0.7 * c->mouse_x / 300);
		v->n_im = 2 * v->o_re * v->o_im + (0.27015 * c->mouse_y / 300);
	}
	else if (c->fractal == conan)
	{
		v->n_re = v->o_re * v->o_re - v->o_im * v->o_im +
			(-0.7 * c->mouse_x / 300) /
			(v->o_re * v->o_re - v->o_im * v->o_im);
		v->n_im = 2 * v->o_re * v->o_im + 0.27015 /
			(v->o_re * v->o_im);
	}
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
