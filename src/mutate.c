/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:47:44 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/15 11:17:37 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	switch_fractal(t_canvas *c, t_fractal f)
{
    if (c->zoom != 1 || c->max_iter != 50 ||
        c->offset_x != 0 || c->offset_y != 0 ||
        c->fractal != f)
        {
            c->zoom = 1;
            c->max_iter = 50;
            c->offset_x = 0;
            c->offset_y = 0;
            c->fractal = f;
            draw(c);
        }
}

void    zoom(t_canvas *c,int direction, double value)
{
    if (direction > 0)
        c->zoom *= value;
    else if ((c->zoom / value) > 0.0125)
        c->zoom /= value;
    else
        return ;
    draw(c);
}

void    move(t_canvas *c, double *direction, double value)
{
    *direction += value / c->zoom;
    draw(c);
}

void    change_iter(t_canvas *c, int value)
{
    c->max_iter + value > 50 ? c->max_iter += value : 0;
    draw(c);
}
