/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 22:11:24 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/02 15:24:55 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_canvas    init(int f)
{
    t_canvas    *c;

    if (!(c = malloc(sizeof(t_canvas))))
		check_error(0, "failed to malloc canvas.");
    c->mlx = mlx_init();
    c->window = mlx_new_window(c->mlx, WIN_WIDTH, WIN_HEIGHT, "fract_ol");
    c->img.width = WIN_WIDTH - OFF_X;
	c->img.height = WIN_HEIGHT - OFF_Y;
	c->img.ptr = mlx_new_image(c->mlx, c->img.width, c->img.height);
	c->img.data = (int *)mlx_get_data_addr(c->img.ptr,
			&c->img.bpp, &c->img.sl, &c->img.e);
	c->fractal = f;
	c->start = 0;
	c->end = 0;
	c->zoom = 1;
	c->max_iter = 50;
	c->offset_x = 0;
	c->offset_y = 0;
	c->color = 0xFFFFFF;
    return (*c);
}

int     main(int argc, char **argv)
{
    t_canvas c;

    if (argc != 2 || argv[1][1] != '\0' || 
		!(1 <= argv[1][0] - '0' && argv[1][0] - '0' <= 4))
        usage();
    c = init(argv[1][0] - '0');
    pthread(&c);
	mlx_hook(c.window, 2, 0, key_hold, &c);
	mlx_hook(c.window, 6, 0, mouse_motion, &c);
    mlx_key_hook(c.window, key_up, &c);
	mlx_mouse_hook(c.window, mouse_click, &c);
    mlx_loop(c.mlx);
    return (0);
}

void	usage(void)
{
	ft_putstr("usage: ./fractol <FRACTAL #>\n");
	ft_putstr("---------------\n   FRACTALS\n---------------\n");
	ft_putstr("1: Mandelbrot\n");
	ft_putstr("2: Julia\n");
	ft_putstr("3: Burning Ship\n");
	ft_putstr("4: Triforce\n");
	exit(0);
}

void	check_error(int err, char *msg)
{
	if (err < 1)
	{
		ft_putstr("- ERROR: ");
		ft_putstr(msg);
		ft_putstr("\n");
		exit(1);
	}
}