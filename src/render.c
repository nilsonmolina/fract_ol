/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:18:52 by nmolina           #+#    #+#             */
/*   Updated: 2018/05/17 17:10:12 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_fractal_thread(t_canvas *c, pthread_t *t)
{
	if (c->fractal == mandelbrot)
		pthread_create(t, NULL, mandelbrot_set, c);
	else if (c->fractal == burning_ship)
		pthread_create(t, NULL, mandelbrot_set, c);
	else if (c->fractal == julia)
		pthread_create(t, NULL, julia_set, c);
	else if (c->fractal == swirlia)
		pthread_create(t, NULL, julia_set, c);
}

void	put_strings(void *mlx, void *w, t_canvas *c)
{
	char		*str;
	t_fractal	f;

	f = c->fractal;
	mlx_string_put(mlx, w, 10, 0, WH, "----------------");
	f == mandelbrot ? mlx_string_put(mlx, w, 20, 15, WH, "Mandelbrot") : 0;
	f == burning_ship ? mlx_string_put(mlx, w, 20, 15, WH, "Burning Ship") : 0;
	f == julia ? mlx_string_put(mlx, w, 20, 15, WH, "Julia") : 0;
	f == swirlia ? mlx_string_put(mlx, w, 20, 15, WH, "Swirlia") : 0;
	mlx_string_put(mlx, w, 10, 30, WH, "----------------");
	mlx_string_put(mlx, w, 15, 50, WH, "Iters:");
	mlx_string_put(mlx, w, 100, 50, WH, str = ft_itoa(c->max_iter));
	free(str);
	mlx_string_put(mlx, w, 15, 70, WH, "Threads:");
	mlx_string_put(mlx, w, 100, 70, WH, str = ft_itoa(c->thr_c));
	free(str);
	mlx_string_put(mlx, w, 15, 90, WH, "Color:");
	mlx_string_put(mlx, w, 100, 90, WH, str = ft_itoa(c->color));
	free(str);
}

void	draw(t_canvas *c)
{
	pthread_t	t_arr[c->thr_c];
	t_canvas	c_arr[c->thr_c];
	int			i;

	mlx_clear_window(c->mlx, c->window);
	ft_bzero(c->img.data, sizeof(int) * c->img.width * c->img.height);
	i = -1;
	while (++i < c->thr_c && (ft_memcpy((void*)&c_arr[i], c, sizeof(t_canvas))))
	{
		c_arr[i].start = i * (WIN_WIDTH / c->thr_c);
		c_arr[i].end = (i + 1) * (WIN_WIDTH / c->thr_c);
	}
	i = -1;
	while (++i < c->thr_c)
		create_fractal_thread(&c_arr[i], &t_arr[i]);
	while (--i >= 0)
		pthread_join(t_arr[i], NULL);
	mlx_put_image_to_window(c->mlx, c->window, c->img.ptr, 0, 0);
	put_strings(c->mlx, c->window, c);
}

void	put_img_vector(t_canvas *c, int x, int y, int color)
{
	int	i;

	if (x > c->img.width - 1 || x < 1)
		return ;
	i = (x) + ((y) * c->img.width);
	if (i >= (c->img.width * c->img.height) || i < 0)
		return ;
	c->img.data[i] = color * c->color;
}

void	change_threads(t_canvas *c)
{
	c->thr_c >= 16 ? c->thr_c = 1 : (c->thr_c *= 2);
	draw(c);
}
