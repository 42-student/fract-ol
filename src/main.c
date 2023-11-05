/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:07 by smargine          #+#    #+#             */
/*   Updated: 2023/09/29 02:55:02 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac == 2 || ac == 4)
	{
		ft_initialize(ac, av, &vars);
		ft_check_args(ac, av, &vars);
		vars.mlx.init = mlx_init(WIDTH, HEIGHT, vars.fractol.name, false);
		if (!vars.mlx.init)
			mlx_terminate(vars.mlx.init);
		vars.mlx.img = mlx_new_image(vars.mlx.init, WIDTH, HEIGHT);
		if (!vars.mlx.img || \
			mlx_image_to_window(vars.mlx.init, vars.mlx.img, 0, 0))
		{
			mlx_delete_image(vars.mlx.init, vars.mlx.img);
			mlx_terminate(vars.mlx.init);
		}
		mlx_loop_hook(vars.mlx.init, &ft_check_user_input, &vars);
		mlx_loop(vars.mlx.init);
		mlx_delete_image(vars.mlx.init, vars.mlx.img);
		mlx_terminate(vars.mlx.init);
	}
	else
		ft_info_user();
	return (0);
}

void	ft_initialize(int ac, char **av, t_vars *vars)
{
	vars->fractol.max_i = 96;
	if (!ft_strncmp(av[1], "tricorn", 8))
		vars->keys.scale = 7;
	else
		vars->keys.scale = 5;
	vars->keys.vertical = 0.0;
	if (!ft_strncmp(av[1], "mandelbrot", 11))
		vars->keys.horizontal = -0.5;
	else
		vars->keys.horizontal = 0.0;
	if (ac == 2 && !ft_strncmp(av[1], "julia", 6))
	{
		vars->fractol.mo = 0.012;
		vars->fractol.ar = (t_complex){0.285, 0.01};
	}
}

void	ft_check_args(int ac, char **av, t_vars *vars)
{
	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 11))
		vars->fractol.name = "mandelbrot";
	else if (ac == 2 && !ft_strncmp(av[1], "julia", 6))
		vars->fractol.name = "julia";
	else if (ac == 4 && !ft_strncmp(av[1], "julia", 6))
	{
		vars->fractol.name = "julia";
		vars->fractol.mo = 0.012;
		vars->fractol.ar = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
	}
	else if (ac == 2 && !ft_strncmp(av[1], "tricorn", 8))
		vars->fractol.name = "tricorn";
	else
		ft_info_user();
}

void	ft_info_user(void)
{
	ft_putendl_fd("\n\e[1;31m{[-_-]}\e[0m \e[4;31mWelcome to fract'ol 42\e[0m\n\n", 1);
	ft_putendl_fd("\e[0;34m~ for Mandelbrot fractal, type:\e[0m \
./fractol mandelbrot\n", 1);
	ft_putendl_fd("\e[0;34m~ for Julia fractal, type:\e[0m \
./fractol julia\n", 1);
	ft_putendl_fd("\e[0;35m~ you can chose the starting point for Julia fractal, \
type:\e[0m ./fractol julia <param_1> <param_2>", 1);
	ft_putendl_fd("\e[0;32m\t> one example: ./fractol julia -0.8 0.156", 1);
	ft_putendl_fd("\t> another example: ./fractol julia -0.4 0.6", 1);
	ft_putendl_fd("\t> and one more example: ./fractol julia \
-0.70176 -0.3842\e[0m\n", 1);
	ft_putendl_fd("\e[0;34m~ for Tricorn fractal, type:\e[0m \
./fractol tricorn\n", 1);
	ft_putendl_fd("\e[0;36m- just for Julia, you can use '+' \
or '-' to shift Julia set;\n", 1);
	ft_putendl_fd("- you can use the mouse wheel to zoom in/out;\n", 1);
	ft_putendl_fd("- you can use '*' or '/' keys to change the \
number of iteration of the fractals;\e[0m\n", 1);
	exit(0);
}
