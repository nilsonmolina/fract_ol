/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:14:06 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/01 20:51:38 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hold(int key, t_canvas *c)
{
    if (c != NULL)
        printf("KEY_HOLD - key: %d\n", key);
	key == 53 ? exit(0) : 0;    
	return (0);
}

int		key_up(int key, t_canvas *c)
{
    if (c != NULL)
        printf("KEY_UP - key: %d\n", key);
	key == 53 ? exit(0) : 0;
	return (0);
}

int		mouse_motion(int x, int y, t_canvas *c)
{
    if (c != NULL)
        printf("MOUSE_MOTION - x: %d | y: %d\n", x, y);
	return (0);
}

int		mouse_click(int mouse, int x, int y, t_canvas *c)
{
    if (c != NULL)
        printf("MOUSE_CLICK - mouse: %d | x: %d | y: %d\n", mouse, x, y);
	return (0);
}