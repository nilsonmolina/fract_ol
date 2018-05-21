/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 05:45:36 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/21 14:55:13 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    set_vars(t_canvas *c, t_vars *v)
{
    v->pr = 1.5 * (v->x - c->img.width / 2) /
        (0.25 * c->zoom * c->img.width) + c->offset_x;
    v->pi = (c->start - c->img.height / 2) /
        (0.25 * c->zoom * c->img.height) + c->offset_y;
    v->n_re = 0;
    v->n_im = 0;
    v->o_re = 0;
    v->o_im = 0;
    v->i = -1;
}

void    set_fractal(t_canvas *c, t_vars *v)
{
    v->o_re =v->n_re;
    v->o_im =v->n_im;
    v->n_re = v->o_re * v->o_re - v->o_im * v->o_im + v->pr;
    if (c->fractal == mandelbrot)
        v->n_im = 2 * v->o_re * v->o_im + v->pi;
    else if (c->fractal == burning_ship)
        v->n_im = 2 * fabs(v->o_re * v->o_im) + v->pi;
}

void    *mandelbrot_set(void* param)
{
    INIT
	while (c->start < c->end)
	{
		v->x = -1;
		while (++v->x < c->img.width)
		{
			set_vars(c, v);
			while (++v->i < c->max_iter)
			{
				set_fractal(c, v);
				if ((v->n_re *v->n_re +v->n_im *v->n_im) > 4)
					break;
				v->i++;
			}
			(v->i < c->max_iter) ? put_img_vector(c, v->x, c->start, v->i) : 0;
		}
		c->start++;
	}
    free(v);
	return(NULL);
}

// void    set_fractal(t_canvas *c, double (*p)[2], double (*o)[2], double (*n)[2])
// {
//     *o[0] = *n[0];
//     *o[1] = *n[1];
//     *n[0] = *o[0] * *o[0] - *o[1] * *o[1] + *p[0];
//     if (c->fractal == mandelbrot)
//         *n[1] = 2 * *o[0] * *o[1] + *p[1];
//     else if (c->fractal == burning_ship)
//         *n[1] = 2 * fabs(*o[0] * *o[1]) + *p[1];
// }

// void    set_zero(int *i, double (*o)[2], double (*n)[2])
// {
//     *n[0] = 0;
//     *n[1] = 0;
//     *o[0] = 0;
//     *o[1] = 0;
//     *i = -1;
// }

// void    *mandelbrot_set(void* param)
// {
// 	t_canvas	*c;
// 	MS_VARS;

// 	c = (t_canvas *)param;
// 	y = c->start - 1;
// 	while (++y < c->end)
// 	{
// 		x = -1;
// 		while (++x < c->img.width)
// 		{
// 			p[0] = 1.5 * (x - c->img.width / 2) / (0.25 * c->zoom * c->img.width) + c->offset_x;
// 			p[1] = (y - c->img.height / 2) / (0.25 * c->zoom * c->img.height) + c->offset_y;
// 			// set_zero(&i, &o, &n);
//             n[0] = 0;
//             n[1] = 0;
//             o[0] = 0;
//             o[1] = 0;
//             i = -1;
// 			while (++i < c->max_iter)
// 			{
// 				set_fractal(c, &p, &o, &n);
// 				if ((n[0] * n[0] + n[1] * n[1]) > 4)
// 					break;
// 			}
// 			if (i < c->max_iter)
// 				put_img_vector(c, x, y, i);
// 		}
// 	}
// 	return(NULL);
// }