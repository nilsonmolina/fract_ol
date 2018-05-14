/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:18:52 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/14 00:08:57 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw(t_canvas *c)
{
	pthread_t	t_arr[THREADS];
	t_canvas	c_arr[THREADS];
	int			i;

	ft_bzero(c->img.data, sizeof(int) * c->img.width * c->img.height);
	i = -1;
	while (++i < THREADS && (ft_memcpy((void*)&c_arr[i], c, sizeof(t_canvas))))
	{
		c_arr[i].start = i * (WIN_WIDTH / THREADS);
		c_arr[i].end = (i + 1) * (WIN_WIDTH / THREADS);
	}
	i = -1;
	while (++i < THREADS)
	{
		if (c->fractal == mandelbrot)
			pthread_create(&t_arr[i], NULL, mandelbrot_set, &c_arr[i]);
		else if (c->fractal == julia)
			pthread_create(&t_arr[i], NULL, julia_set, &c_arr[i]);
		else if (c->fractal == burning_ship)
			pthread_create(&t_arr[i], NULL, mandelbrot_set, &c_arr[i]);
		else if (c->fractal == triforce)
			pthread_create(&t_arr[i], NULL, julia_set, &c_arr[i]);
	}
	while (--i >= 0)
		pthread_join(t_arr[i], NULL);
	mlx_put_image_to_window(c->mlx, c->window, c->img.ptr, 0, 0);
}

void	put_img_vector(t_canvas *c, int x, int y)
{
	int	i;

    if (x > c->img.width - 1 || x < 1)
        return ;
    i = (x) + ((y) * c->img.width);
    if (i >= (c->img.width * c->img.height) || i < 0)
        return ;
    c->img.data[i] = c->color;
}