/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:27 by smargine          #+#    #+#             */
/*   Updated: 2023/09/29 04:30:32 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define PRECISION 1.024669

typedef struct s_mlx
{
	mlx_t		*init;
	mlx_image_t	*img;
}	t_mlx;

typedef struct s_keys
{
	double	horizontal;
	double	vertical;
	double	scale;
}	t_keys;

typedef struct s_mouse
{
	int32_t	x;
	int32_t	y;
	double	move_x;
	double	move_y;
}	t_mouse;

typedef struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_fractol
{
	char		*name;
	int			pos_x;
	int			pos_y;
	t_complex	c;
	t_complex	z;
	int			i;
	int			max_i;
	t_complex	ar;
	double		mo;
}	t_fractol;

typedef struct s_vars
{
	t_mlx		mlx;
	t_fractol	fractol;
	t_keys		keys;
	t_mouse		mouse;
	t_rgb		rgb;
}	t_vars;

//main
void		ft_initialize(int ac, char **av, t_vars *vars);
void		ft_check_args(int ac, char **av, t_vars *vars);
void		ft_info_user(void);

//user_input
void		ft_check_user_input(void *param);
void		ft_keys_input(t_vars *vars);
void		ft_mouse_scroll(double xdelta, double ydelta, void *param);

//color
void		ft_put_pixel(t_vars *vars);
double		ft_smooth_color(t_vars *vars);
uint32_t	ft_interpolate_color(t_rgb a, t_rgb b, double x);

//fractals
void		ft_select_fractal(t_vars *vars);
void		ft_mandelbrot(t_vars *vars);
void		ft_julia(t_vars *vars);
void		ft_tricorn(t_vars *vars);

#endif