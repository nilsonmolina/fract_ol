/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:11:24 by nmolina           #+#    #+#             */
/*   Updated: 2018/04/30 23:45:56 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     main(int argc, char **argv)
{
    t_canvas c;

    if (argc != 2)
		usage();
    c.mlx = mlx_init();
    c.window = mlx_new_window(c.mlx, WIN_WIDTH, WIN_HEIGHT, "fract_ol");
    c.img.width = WIN_WIDTH - OFF_X;
	c.img.height = WIN_HEIGHT - OFF_Y;
	c.img.img = mlx_new_image(c.mlx, c.img.width, c.img.height);
	c.img.data = (int *)mlx_get_data_addr(c.img.img,
			&c.img.bpp, &c.img.sl, &c.img.e);

    mlx_loop(c.mlx);
    return (0);
}

void	usage(void)
{
	ft_putstr("usage: ./fractol <FRACTAL>\n");
	exit(0);
}