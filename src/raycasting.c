/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakemrezeper <burakemrezeper@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 16:14:20 by burakemreze      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_ray(t_ray *ray, int x, t_cub3d *cub)
{
	double	camera_x;

	camera_x = 2 * x / (double)WWINDOW - 1;
	ray->dir_x = cub->player.dir.x + cub->player.plane.x * camera_x;
	ray->dir_y = cub->player.dir.y + cub->player.plane.y * camera_x;
	ray->map_x = (int)cub->player.pos.x;
	ray->map_y = (int)cub->player.pos.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.pos.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.pos.y)
			* ray->delta_dist_y;
	}
}

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
	// Assuming texture width of 64
	draw->tex_x = (int)(draw->wall_x * 64);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->tex_x = 64 - draw->tex_x - 1;
}

void	cast_ray(int x, t_cub3d *cub)
{
	t_ray	ray;
	t_draw	draw;

	init_ray(&ray, x, cub);
	perform_dda(&ray, cub);
	calculate_wall(&ray, &draw, cub);
	// draw_wall; // implement it here:
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