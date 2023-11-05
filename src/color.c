/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:07 by smargine          #+#    #+#             */
/*   Updated: 2023/09/29 05:51:00 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	ft_put_pixel(t_vars *vars)
{
	u_int32_t	color;
	t_rgb		*palette;
	t_rgb		a;
	t_rgb		b;
	double		cv;

	palette = (t_rgb[64]){{255, 0, 0}, {255, 16, 0}, {255, 32, 0}, {255, 48, 0 \
	}, {255, 64, 0}, {255, 80, 0}, {255, 96, 0}, {255, 112, 0}, {255, 128, 0}, \
	{255, 160, 0}, {255, 192, 0}, {255, 224, 0}, {255, 240, 0}, {255, 255, 0}, \
	{239, 255, 0}, {223, 255, 0}, {207, 255, 0}, {191, 255, 0}, {175, 255, 0}, \
	{159, 255, 0}, {143, 255, 0}, {127, 255, 0}, {111, 255, 0}, {95, 255, 0}, \
	{63, 255, 0}, {31, 255, 0}, {0, 255, 0}, {0, 255, 16}, {0, 255, 64}, \
	{0, 255, 96}, {0, 255, 112}, {0, 255, 136}, {0, 255, 152}, {0, 255, 168}, \
	{0, 255, 200}, {0, 255, 216}, {0, 255, 232}, {0, 255, 255}, {0, 239, 255}, \
	{0, 231, 255}, {0, 223, 255}, {0, 215, 255}, {0, 199, 255}, {0, 191, 255}, \
	{0, 183, 255}, {0, 175, 255}, {0, 159, 255}, {0, 151, 255}, {0, 142, 255}, \
	{0, 127, 255}, {0, 111, 255}, {0, 95, 255}, {0, 63, 255}, {0, 31, 255}, \
	{0, 0, 255}, {32, 0, 224}, {224, 0, 208}, {64, 0, 192}, {96, 0, 160}, \
	{128, 0, 128}, {160, 0, 96}, {192, 0, 64}, {223, 0, 32}, {255, 0, 0}};
	cv = ft_smooth_color(vars);
	a = palette[(int)floor(cv) % 60];
	b = palette[((int)floor(cv) + 1) % 60];
	color = ft_interpolate_color(a, b, cv - floor(cv));
	mlx_put_pixel(vars->mlx.img, vars->fractol.pos_x, \
		vars->fractol.pos_y, color);
}

double	ft_smooth_color(t_vars *vars)
{
	double	magnitude;
	double	normalize;

	magnitude = log(vars->fractol.z.real * vars->fractol.z.real + \
		vars->fractol.z.imaginary * vars->fractol.z.imaginary) / 2.0;
	normalize = log(magnitude / log(2)) / log(2);
	if (vars->fractol.i < vars->fractol.max_i)
		return (vars->fractol.i + 1 - normalize);
	else if (vars->fractol.i > 0)
		return (vars->fractol.max_i);
	else
		return (0.0);
}

uint32_t	ft_interpolate_color(t_rgb a, t_rgb b, double x)
{
	t_rgb	res;

	res.r = a.r + (b.r - a.r) * x;
	res.g = a.g + (b.g - a.g) * x;
	res.b = a.b + (b.b - a.b) * x;
	return (res.r << 24 | res.g << 16 | res.b << 8 | 255);
}
