/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:07 by smargine          #+#    #+#             */
/*   Updated: 2023/09/29 04:30:38 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	ft_check_user_input(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx.init);
	ft_keys_input(vars);
	mlx_scroll_hook(vars->mlx.init, &ft_mouse_scroll, vars);
	ft_select_fractal(vars);
}

void	ft_keys_input(t_vars *vars)
{
	double	hor;
	double	ver;

	hor = 2 * vars->keys.scale * 0.02;
	ver = -2 * vars->keys.scale * 0.02;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_UP))
		vars->keys.vertical += ver;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_DOWN))
		vars->keys.vertical -= ver;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_LEFT))
		vars->keys.horizontal -= hor;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_RIGHT))
		vars->keys.horizontal += hor;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_KP_MULTIPLY))
		vars->fractol.max_i = vars->fractol.max_i * 1.1 + 1;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_KP_DIVIDE))
		vars->fractol.max_i /= 1.1;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_KP_ADD))
		vars->fractol.mo += 1 * 0.01;
	if (mlx_is_key_down(vars->mlx.init, MLX_KEY_KP_SUBTRACT))
		vars->fractol.mo -= 1 * 0.01;
}

void	ft_mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_vars	*vars;

	vars = param;
	mlx_get_mouse_pos(vars->mlx.init, &vars->mouse.x, &vars->mouse.y);
	if (vars->mouse.x < 0 || vars->mouse.y < 0 || xdelta > WIDTH \
		|| vars->mouse.x >= WIDTH || vars->mouse.y >= HEIGHT)
		return ;
	vars->mouse.move_x = (vars->mouse.x - WIDTH / 2.0) \
		* vars->keys.scale / WIDTH;
	vars->mouse.move_y = (vars->mouse.y - HEIGHT / 2.0) \
		* vars->keys.scale / HEIGHT;
	if (ydelta > 0)
	{
		vars->keys.scale *= 1.1;
		vars->keys.vertical += vars->mouse.move_y - (vars->mouse.y \
			- HEIGHT / 2.0) * vars->keys.scale / (HEIGHT * PRECISION);
	}
	else if (ydelta < 0)
	{
		vars->keys.scale /= 1.1;
		vars->keys.vertical += vars->mouse.move_y - (vars->mouse.y \
			- HEIGHT / 2.0) * vars->keys.scale * PRECISION / HEIGHT;
	}
	vars->keys.horizontal += vars->mouse.move_x - \
		(vars->mouse.x - WIDTH / 2.0) * vars->keys.scale / WIDTH;
}
