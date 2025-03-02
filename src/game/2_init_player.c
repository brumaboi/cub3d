/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:06:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/02 19:06:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int direction_ns(t_cub3d *cub)
{
    if(cub->map.player == 0)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
		cub->player.plane.x = 0.66;
		cub->player.plane.y = 0;
	}
	else if(cub->map.player == 1)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
		cub->player.plane.x = -0.66;
		cub->player.plane.y = 0;
	}
	else
	{
		return (1);
	}
	return (0);
}

static int direction_ew(t_cub3d *cub)
{
    if(cub->map.player == 2)
	{
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
		cub->player.plane.x = 0;
		cub->player.plane.y = -0.66;
	}
	else if(cub->map.player == 3)
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
		cub->player.plane.x = 0;
		cub->player.plane.y = 0.66;
	}
	else
	{
		printf("Error: Invalid player direction\n");
		return (1);
	}
	return (0);
}

int init_player(t_cub3d *cub)
{
    cub->player.pos.x = cub->map.player_pos.x;
    cub->player.pos.y = cub->map.player_pos.y;
    if(cub->map.player == 0 || cub->map.player == 1)
	{
		if(direction_ns(cub))
			return (1);
	}
	else
	{
		if(direction_ew(cub))
			return (1);
	}
    cub->player.walk_speed = 0.05;
    cub->player.turn_speed = 0.05;
    return (0);
}
