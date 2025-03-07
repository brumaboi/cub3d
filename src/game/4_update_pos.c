/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_update_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:23:19 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/07 14:14:16 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	update_rotate_left(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cub->player.input_rotate_left)
	{
		old_dir_x = cub->player.dir.x;
		cub->player.dir.x = cub->player.dir.x * cos(cub->player.turn_speed)
			- cub->player.dir.y * sin(cub->player.turn_speed);
		cub->player.dir.y = old_dir_x * sin(cub->player.turn_speed)
			+ cub->player.dir.y * cos(cub->player.turn_speed);
		old_plane_x = cub->player.plane.x;
		cub->player.plane.x = cub->player.plane.x * cos(cub->player.turn_speed)
			- cub->player.plane.y * sin(cub->player.turn_speed);
		cub->player.plane.y = old_plane_x * sin(cub->player.turn_speed)
			+ cub->player.plane.y * cos(cub->player.turn_speed);
	}
}

void	update_rotate_right(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cub->player.input_rotate_right)
	{
		old_dir_x = cub->player.dir.x;
		cub->player.dir.x = cub->player.dir.x * cos(-cub->player.turn_speed)
			- cub->player.dir.y * sin(-cub->player.turn_speed);
		cub->player.dir.y = old_dir_x * sin(-cub->player.turn_speed)
			+ cub->player.dir.y * cos(-cub->player.turn_speed);
		old_plane_x = cub->player.plane.x;
		cub->player.plane.x = cub->player.plane.x * cos(-cub->player.turn_speed)
			- cub->player.plane.y * sin(-cub->player.turn_speed);
		cub->player.plane.y = old_plane_x * sin(-cub->player.turn_speed)
			+ cub->player.plane.y * cos(-cub->player.turn_speed);
	}
}

void	update_player(t_cub3d *cub)
{
	double	move_speed;

	move_speed = cub->player.walk_speed;
	update_forward(cub, move_speed);
	update_backward(cub, move_speed);
	update_left(cub, move_speed);
	update_right(cub, move_speed);
	update_rotate_left(cub);
	update_rotate_right(cub);
}
