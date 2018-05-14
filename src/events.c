/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:06 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/14 14:54:49 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hold(int key, t_canvas *c)
{
    // printf("KEY_HOLD - key: %d\n", key);
    if (key == 53)
	{
        mlx_destroy_image(c->mlx, c->img.ptr);
		mlx_destroy_window(c->mlx, c->window);
		exit(0);
	}
    key == 6 ? c->zoom *= 1.25 : 0;
	key == 7 && (c->zoom / 1.25 > 0) ? c->zoom /= 1.25 : 0;
	key == 123 ? c->offset_x += 0.3/c->zoom : 0;
	key == 124 ? c->offset_x -= 0.3/c->zoom : 0;
	key == 125 ? c->offset_y -= 0.3/c->zoom : 0;
	key == 126 ? c->offset_y += 0.3/c->zoom : 0;
    if (key == 6 || key == 7 || (123 <= key && key <= 126))
    {
        draw(c);        
        // printf("zoom: %f | offset_x: %f | offset_y: %f\n", c->zoom, c->offset_x, c->offset_y);        
    }
	return (0);
}

// int		key_up(int key, t_canvas *c)
// {
//     if (c != NULL)
//         printf("KEY_UP - key: %d\n", key);
// 	return (0);
// }

int		mouse_motion(int x, int y, t_canvas *c)
{
    // if (c != NULL)
    //     printf("MOUSE_MOTION - x: %d | y: %d\n", x, y);
    if ((c->fractal == julia || c->fractal == 4) && 
        x >= 0 && y >= 0 && x <= c->img.width && y <= c->img.height)
	{
		c->mouse_x = x;
		c->mouse_y = y;
		draw(c);
	}
	return (0);
}

int		mouse_click(int mouse, int x, int y, t_canvas *c)
{
    if (c != NULL)
        printf("MOUSE_CLICK - mouse: %d | x: %d | y: %d\n", mouse, x, y);
	mouse == 4 ? c->zoom *= 1.25 : 0;
	mouse == 5 && (c->zoom / 1.25 > 0.125) ? c->zoom /= 1.25 : 0;
	draw(c);	
	
	return (0);
}