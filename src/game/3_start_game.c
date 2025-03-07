/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_start_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:31:25 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/07 14:14:49 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clear_screen(t_cub3d *cub)
{
	int	x;
	int	y;

	if (cub->bg_img)
		mlx_delete_image(cub->mlx, cub->bg_img);
	cub->bg_img = mlx_new_image(cub->mlx, WWINDOW, HWINDOW);
	if (!cub->bg_img)
	{
		printf("Error: Failed to create new image\n");
		return ;
	}
	y = 0;
	while (y < HWINDOW)
	{
		x = 0;
		while (x < WWINDOW)
		{
			if (y < HWINDOW / 2)
				mlx_put_pixel(cub->bg_img, x, y, cub->map.ceiling_color);
			else
				mlx_put_pixel(cub->bg_img, x, y, cub->map.floor_color);
			x++;
		}
		y++;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cub->mlx);
	return ;
}

void	handle_input(t_cub3d *cub)
{
	cub->player.input_forward = mlx_is_key_down(cub->mlx, MLX_KEY_W);
	cub->player.input_backward = mlx_is_key_down(cub->mlx, MLX_KEY_S);
	cub->player.input_strafe_left = mlx_is_key_down(cub->mlx, MLX_KEY_A);
	cub->player.input_strafe_right = mlx_is_key_down(cub->mlx, MLX_KEY_D);
	cub->player.input_rotate_left = mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT);
	cub->player.input_rotate_right = mlx_is_key_down(cub->mlx, MLX_KEY_LEFT);
}

void	game_loop(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	handle_input(cub);
	update_player(cub);
	clear_screen(cub);
	raycaster(cub);
}

int	start_game(t_cub3d *cub)
{
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
