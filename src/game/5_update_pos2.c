/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_pos2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:20:58 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/05 13:24:16 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_hit(t_cub3d *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= cub->map.rows
		|| map_x < 0 || map_x >= cub->map.columns)
		return (0);
	return (is_walkable(cub->map.map[map_y][map_x]));
}

void	update_forward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	if (cub->player.input_forward)
	{
		new_x = cub->player.pos.x + cub->player.dir.x * move_speed;
		new_y = cub->player.pos.y + cub->player.dir.y * move_speed;
		if (check_hit(cub, new_x, new_y))
		{
			cub->player.pos.x = new_x;
			cub->player.pos.y = new_y;
		}
	}
}

void	update_backward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	if (cub->player.input_backward)
	{
		new_x = cub->player.pos.x - cub->player.dir.x * move_speed;
		new_y = cub->player.pos.y - cub->player.dir.y * move_speed;
		if (check_hit(cub, new_x, new_y))
		{
			cub->player.pos.x = new_x;
			cub->player.pos.y = new_y;
		}
	}
}

void	update_left(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	if (cub->player.input_strafe_left)
	{
		new_x = cub->player.pos.x - cub->player.plane.x * move_speed;
		new_y = cub->player.pos.y - cub->player.plane.y * move_speed;
		if (check_hit(cub, new_x, new_y))
		{
			cub->player.pos.x = new_x;
			cub->player.pos.y = new_y;
		}
	}
}

void	update_right(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	if (cub->player.input_strafe_right)
	{
		new_x = cub->player.pos.x + cub->player.plane.x * move_speed;
		new_y = cub->player.pos.y + cub->player.plane.y * move_speed;
		if (check_hit(cub, new_x, new_y))
		{
			cub->player.pos.x = new_x;
			cub->player.pos.y = new_y;
		}
	}
}
