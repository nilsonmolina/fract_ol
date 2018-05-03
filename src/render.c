/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:18:52 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/02 15:01:53 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pthread(t_canvas *c)
{
	int			i;
	t_canvas	c_arr[4];
	pthread_t	tid[THREADS];

	// ft_bzero(c->img.data, sizeof(int) * c->img.width * c->img.height);
	i = -1;
	while (++i < THREADS && (ft_memcpy((void*)&c_arr[i], c, sizeof(t_canvas))))
	{
		c_arr[i].start = i * 200;
		c_arr[i].end = (i + 1) * 200;
	}
	i = -1;
	while (++i < 4)
		if (c->fractal == mandelbrot)
			pthread_create(&tid[i], NULL, mandelbrot_set, &c_arr[i]);
	while (--i >= 0)
		pthread_join(tid[i], NULL);
	mlx_put_image_to_window(c->mlx, c->window, c->img.ptr, 0, 0);
}

void	put_img_vector(t_canvas *c, int x, int y)
{
	int	i;

    if (x > c->img.width - 1 || x < 1)
        return ;
    i = (x) + ((y) * c->img.width);
    // if (i > (c->img.width * c->img.height) || i < 0)
    if (i >= (c->img.width * c->img.height) || i < 0)
        return ;
    c->img.data[i] = c->color;
}