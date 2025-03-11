/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:20:59 by ezeper            #+#    #+#             */
/*   Updated: 2025/03/11 14:26:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_cub3d *cub)
{
	double	new_pos_x;
	double	new_pos_y;

	printf("DEBUG: Moving forward Before move: new_pos_x = %f new_pos_y + %f\n",
		cub->player.pos.x, cub->player.pos.y);
	new_pos_x = cub->player.pos.x + cub->player.dir.x * cub->player.walk_speed;
	new_pos_y = cub->player.pos.y + cub->player.dir.y * cub->player.walk_speed;
	if (cub->map.map[(int)new_pos_y][(int)cub->player.pos.x] != WALL)
		cub->player.pos.y = new_pos_y;
	if (cub->map.map[(int)cub->player.pos.y][(int)new_pos_x] != WALL)
		cub->player.pos.x = new_pos_x;
	printf("DEBUG: Moving forward After move: new_pos_x = %f new_pos_y + %f\n",
		cub->player.pos.x, cub->player.pos.y);
}
