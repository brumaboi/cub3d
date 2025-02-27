/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:00:00 by marvin            #+#    #+#             *//*   Updated: 2025/02/27 19:08:12 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_ray_plane(t_ray *ray, int x, t_cub3d *cub)
{
    double camera_x;

    camera_x = 2 * x / (double)WWINDOW - 1;
    ray->dir_x = cub->player.dir.x + cub->player.plane.x * camera_x;
    ray->dir_y = cub->player.dir.y + cub->player.plane.y * camera_x;
    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->dir_x);
    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void init_ray_player(t_ray *ray, t_cub3d *cub)
{
	ray->map_x = (int)cub->player.pos.x;
	ray->map_y = (int)cub->player.pos.y;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.pos.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.pos.y) * ray->delta_dist_y;
	}
}

void	cast_ray(int x, t_cub3d *cub)
{
	t_ray	ray;
	t_draw	draw;

	init_ray_plane(&ray, x, cub);
    init_ray_player(&ray, cub);
	perform_dda(&ray, cub);
	calculate_wall(&ray, &draw, cub);
	draw_wall(x, &draw, cub);
}

void	raycaster(t_cub3d *cub)
{
	int	x;

    x = 0;
	draw_background(cub);
	while (x < WWINDOW)
	{
		cast_ray(x, cub);
		x++;
	}
}