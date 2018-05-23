/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:06 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/22 22:50:13 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hold(int key, t_canvas *c)
{
	if (key == 53)
		exit(0);
	key == 8 ? change_color(c) : 0;
	key == 6 ? zoom(c, 1.25, -1, -1) : 0;
	key == 7 ? zoom(c, -1.25, -1, -1) : 0;
	key == 12 ? change_iter(c, -1) : 0;
	key == 14 ? change_iter(c, 1) : 0;
	key == 123 ? move(c, &c->offset_x, 0.3) : 0;
	key == 124 ? move(c, &c->offset_x, -0.3) : 0;
	key == 125 ? move(c, &c->offset_y, -0.3) : 0;
	key == 126 ? move(c, &c->offset_y, 0.3) : 0;
	key == 257 ? c->shft = 1 : 0;
	return (0);
}

int		key_up(int key, t_canvas *c)
{
	key == 0 ? move(c, &c->offset_x, -0.3) : 0;
	key == 2 ? move(c, &c->offset_x, 0.3) : 0;
	key == 1 ? move(c, &c->offset_y, 0.3) : 0;
	key == 13 ? move(c, &c->offset_y, -0.3) : 0;
	key == 17 ? change_threads(c) : 0;
	key == 18 ? switch_fractal(c, 1) : 0;
	key == 19 ? switch_fractal(c, 2) : 0;
	key == 20 ? switch_fractal(c, 3) : 0;
	key == 21 ? switch_fractal(c, 4) : 0;
	key == 23 ? switch_fractal(c, 5) : 0;
	key == 46 ? toggle_menu(c) : 0;
	key == 49 ? switch_fractal(c, c->fractal) : 0;
	key == 257 ? c->shft = 0 : 0;
	return (0);
}

int		mouse_motion(int x, int y, t_canvas *c)
{
	if (c->fractal == julia &&
		x >= 0 && y >= 0 && x <= c->img->width && y <= c->img->height)
	{
		c->mouse_x = x;
		c->mouse_y = y;
		draw(c);
	}
	return (0);
}

int		mouse_click(int mouse, int x, int y, t_canvas *c)
{
	mouse == 4 ? zoom(c, 1.25, x, y) : 0;
	mouse == 5 ? zoom(c, -1.25, x, y) : 0;
	return (0);
}

void	toggle_menu(t_canvas *c)
{
	if (c->menu > 1)
		c->menu = -1;
	c->menu++;
	draw(c);
}
