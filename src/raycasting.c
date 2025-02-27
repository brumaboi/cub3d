/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 15:31:07 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	init_ray(t_ray *ray, int x, t_cub3d *game_data)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = game_data->dir_x + game_data->plane_x * camera_x;
	ray->dir_y = game_data->dir_y + game_data->plane_y * camera_x;
	ray->map_x = (int)game_data->pos_x;
	ray->map_y = (int)game_data->pos_y;
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game_data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game_data->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game_data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{1
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game_data->pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_cub3d *game_data)
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
		if (game_data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	calculate_wall(t_ray *ray, t_draw *draw, t_cub3d *game_data)
{
	draw->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		draw->tex_num = (ray->step_x < 0) ? WEST : EAST;
	else
		draw->tex_num = (ray->step_y < 0) ? NORTH : SOUTH;
	if (ray->side == 0)
		draw->wall_x = game_data->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		draw->wall_x = game_data->pos_x + ray->perp_wall_dist * ray->dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->tex_x = TEXTURE_WIDTH - draw->tex_x - 1;
}

static void	draw_wall(int x, t_ray *ray, t_draw *draw, t_cub3d *game_data)
{
	int				y;
	mlx_texture_t	*texture;
	double			step;
	double			tex_pos;
	uint8_t			*color;

	texture = game_data->textures[draw->tex_num];
	step = 1.0 * TEXTURE_HEIGHT / draw->line_height;
	tex_pos = (draw->draw_start - HEIGHT / 2 + draw->line_height / 2) * step;
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		color = &texture->pixels[((int)tex_pos & (TEXTURE_HEIGHT - 1))
			* texture->width + draw->tex_x) * 4];
		mlx_put_pixel(game_data->img, x, y, *(uint32_t *)color);
		tex_pos += step;
		y++;
	}
}

void	cast_ray(int x, t_cub3d *game_data)
{
	t_ray	ray;
	t_draw	draw;

	init_ray(&ray, x, game_data);
	perform_dda(&ray, game_data);
	calculate_wall(&ray, &draw, game_data);
	draw_wall(x, &ray, &draw, game_data);
}

void	raycaster(t_cub3d *game_data)
{
	int	x;

	draw_background(game_data);
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(x, game_data);
		x++;
	}
}