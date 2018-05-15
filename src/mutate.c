/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:47:44 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/15 15:52:46 by nmolina          ###   ########.fr       */
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

void	zoom(t_canvas *c, double value, int x, int y)
{
	if (value > 0)
	{
		c->zoom *= value;
		c->zoom < 180 ? c->max_iter++ : 0;
		if (x > 0 && y > 0)
		{
			c->offset_x += c->img.width / 2 + x;
			c->offset_y += c->img.height / 2 + y;
		}
	}
	else if ((c->zoom / -value) > 0.00125)
	{
		c->zoom /= -value;
		c->max_iter > 50 ? c->max_iter-- : 0;
	}
	else
		return ;
	draw(c);
}

void	move(t_canvas *c, double *direction, double value)
{
	*direction += value / c->zoom;
	draw(c);
}

void	change_iter(t_canvas *c, int value)
{
	c->max_iter + value > 50 ? c->max_iter += value : 0;
	draw(c);
}

void	change_color(t_canvas *c)
{
	if (c->color < 20)
		c->color += 3;
	else
		c->color = 1;
	draw(c);
}
