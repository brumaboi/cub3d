/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:17 by ezeper            #+#    #+#             */
/*   Updated: 2025/02/27 19:06:51 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	perform_dda(t_ray *ray, t_cub3d *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map.map[ray->map_y][ray->map_x] == WALL)
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}
static void	calculate_wall(t_ray *ray, t_draw *draw, t_cub3d *cub)
{
	draw->line_height = (int)(HWINDOW / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + HWINDOW / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HWINDOW / 2;
	if (draw->draw_end >= HWINDOW)
		draw->draw_end = HWINDOW - 1;
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			draw->tex_num = 2;  // WEST
		else
			draw->tex_num = 3;  // EAST
	}
	else
	{
		if (ray->step_y < 0)
			draw->tex_num = 0;  // NORTH
		else
			draw->tex_num = 1;  // SOUTH
	}
	if (ray->side == 0)
		draw->wall_x = cub->player.pos.y + ray->perp_wall_dist * ray->dir_y;
	else
		draw->wall_x = cub->player.pos.x + ray->perp_wall_dist * ray->dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * 64);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->tex_x = 64 - draw->tex_x - 1;
}

// void draw_wall(int i, t_cub3d *cub, t_draw *draw)
// {

// }