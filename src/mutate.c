/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:47:44 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/17 17:11:33 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_canvas *c, double value, int x, int y)
{
	if (value > 0)
		c->zoom *= value;
	else if ((c->zoom / -value) > 0.00125)
		c->zoom /= -value;
	else
		return ;
	if (x > 0 && y > 0)
	{
		c->offset_x += ((x - c->img.width / 2) * 0.00125) / c->zoom;
		c->offset_y += ((y - c->img.height / 2) * 0.00125) / c->zoom;
	}
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
	if (c->color < 0)
		c->color = 10;
	else if (c->color < 1000)
		c->color *= 1.1;
	else
		c->color *= 1.05;
	draw(c);
}
