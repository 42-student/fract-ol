/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:07 by smargine          #+#    #+#             */
/*   Updated: 2023/09/26 21:03:17 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	ft_select_fractal(t_vars *vars)
{
	vars->fractol.pos_x = -1;
	while (++vars->fractol.pos_x < WIDTH)
	{
		vars->fractol.pos_y = -1;
		while (++vars->fractol.pos_y < HEIGHT)
		{
			if (!ft_strncmp(vars->fractol.name, "mandelbrot", 11))
				ft_mandelbrot(vars);
			else if (!ft_strncmp(vars->fractol.name, "julia", 6))
				ft_julia(vars);
			else if (!ft_strncmp(vars->fractol.name, "tricorn", 8))
				ft_tricorn(vars);
		}
	}
}

void	ft_mandelbrot(t_vars *vars)
{
	double	temp;

	vars->fractol.c.real = (vars->fractol.pos_x - WIDTH / 2.0) * \
		vars->keys.scale / WIDTH + vars->keys.horizontal;
	vars->fractol.c.imaginary = (vars->fractol.pos_y - HEIGHT / \
		2.0) * vars->keys.scale / WIDTH + vars->keys.vertical;
	vars->fractol.z = (t_complex){0, 0};
	vars->fractol.i = -1;
	while (++vars->fractol.i < vars->fractol.max_i)
	{
		if ((vars->fractol.z.real * vars->fractol.z.real + \
			vars->fractol.z.imaginary * vars->fractol.z.imaginary) >= 4.0)
			break ;
		temp = 2.0 * vars->fractol.z.real * vars->fractol.z.imaginary \
			+ vars->fractol.c.imaginary;
		vars->fractol.z.real = vars->fractol.z.real * \
			vars->fractol.z.real - vars->fractol.z.imaginary * \
			vars->fractol.z.imaginary + vars->fractol.c.real;
		vars->fractol.z.imaginary = temp;
	}
	ft_put_pixel(vars);
}

void	ft_julia(t_vars *vars)
{
	double	temp;

	vars->fractol.z.real = (vars->fractol.pos_x - WIDTH / 2) * \
		vars->keys.scale / WIDTH + vars->keys.horizontal;
	vars->fractol.z.imaginary = (vars->fractol.pos_y - HEIGHT / 2) * \
		vars->keys.scale / WIDTH + vars->keys.vertical;
	vars->fractol.c.real = vars->fractol.ar.real + vars->fractol.mo;
	vars->fractol.c.imaginary = vars->fractol.ar.imaginary + vars->fractol.mo;
	vars->fractol.i = -1;
	while (++vars->fractol.i < vars->fractol.max_i)
	{
		if ((vars->fractol.z.real * vars->fractol.z.real + \
			vars->fractol.z.imaginary * vars->fractol.z.imaginary) >= 4.0)
			break ;
		temp = 2.0 * vars->fractol.z.real * \
			vars->fractol.z.imaginary + vars->fractol.c.imaginary;
		vars->fractol.z.real = vars->fractol.z.real * \
			vars->fractol.z.real - vars->fractol.z.imaginary * \
			vars->fractol.z.imaginary + vars->fractol.c.real;
		vars->fractol.z.imaginary = temp;
	}
	ft_put_pixel(vars);
}

void	ft_tricorn(t_vars *vars)
{
	double	temp;

	vars->fractol.c.real = (vars->fractol.pos_x - WIDTH / 2.0) * \
		vars->keys.scale / WIDTH + vars->keys.horizontal;
	vars->fractol.c.imaginary = (vars->fractol.pos_y - HEIGHT / 2.0) \
			* vars->keys.scale / WIDTH + vars->keys.vertical;
	vars->fractol.z = (t_complex){0, 0};
	vars->fractol.i = -1;
	while (++vars->fractol.i < vars->fractol.max_i)
	{
		if ((vars->fractol.z.real * vars->fractol.z.real + \
			vars->fractol.z.imaginary * vars->fractol.z.imaginary) >= 4.0)
			break ;
		temp = -2.0 * vars->fractol.z.real * \
			vars->fractol.z.imaginary + vars->fractol.c.imaginary;
		vars->fractol.z.real = vars->fractol.z.real * \
			vars->fractol.z.real - vars->fractol.z.imaginary * \
			vars->fractol.z.imaginary + vars->fractol.c.real;
		vars->fractol.z.imaginary = temp;
	}
	ft_put_pixel(vars);
}
