/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:44:25 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/21 14:50:50 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    set_new(t_canvas *c, t_vars *v)
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
            (-0.7 * c->mouse_x / 300) / (v->o_re * v->o_re - v->o_im * 
        v->o_im);
        v->n_im = 2 * v->o_re * v->o_im + 
            (0.27015 * c->mouse_y / 300) / (v->o_re * v->o_im);
    }
    else if (c->fractal == conan)
    {
        v->n_re = v->o_re * v->o_re - v->o_im * v->o_im +
            (-0.7 * c->mouse_x / 300);
        v->n_im = 2 * v->o_re * v->o_im + (0.27015 * c->mouse_y / 300);
    }
}

void    *julia_set(void *param)
{
	INIT
	while (c->start < c->end)
	{
		v->x = -1;
		while (++v->x < c->img.width)
		{
			v->n_re = 1.5 * (v->x - 400) /
                (0.5 * c->zoom * c->img.width) + c->offset_x;
			v->n_im = (c->start - 300) /
                (0.5 * c->zoom * c->img.height) + c->offset_y;
			v->i = -1;
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



// void    set_new(t_canvas *c, double (*o)[2], double (*n)[2])
// {
//     *o[0] = *n[0];
//     *o[1] = *n[1];
//     if (c->fractal == swirlia)
//     {
//         *n[0] = *o[0] * *o[0] - *o[1] * *o[1] + (-0.7 * 291 / 300);
//         *n[1] = 2 * *o[0] * *o[1] + (0.27015 * 400 / 300);
//     }
//     else if (c->fractal == julia)
//     {
//         *n[0] = *o[0] * *o[0] - *o[1] * *o[1] + (-0.7 * c->mouse_x / 300) / (*o[0] * *o[0] - *o[1] * 
//         *o[1]);
//         *n[1] = 2 * *o[0] * *o[1] + (0.27015 * c->mouse_y / 300) / (*o[0] * *o[1]);
//     }
//     else if (c->fractal == conan)
//     {
//         *n[0] = *o[0] * *o[0] - *o[1] * *o[1] + (-0.7 * c->mouse_x / 300);
//         *n[1] = 2 * *o[0] * *o[1] + (0.27015 * c->mouse_y / 300);
//     }
// }

// void    *julia_set(void *param)
// {
//     JS_VARS;
// 	while (c->start < c->end)
// 	{
// 		x = -1;
// 		while (++x < c->img.width)
// 		{
// 			n[0] = 1.5 * (x - 400) / (0.5 * c->zoom * c->img.width) + c->offset_x;
// 			n[1] = (c->start - 300) / (0.5 * c->zoom * c->img.height) + c->offset_y;
// 			i = -1;
// 			while (++i < c->max_iter)
// 			{
//                 set_new(c, &o, &n);
//                 if ((n[0] * n[0] + n[1] * n[1]) > 4)
//                     break ;
// 			}
// 			(i < c->max_iter) ? put_img_vector(c, x, c->start, i) : 0;
// 		}
//         c->start++;
// 	}
// 	return (NULL);
// }