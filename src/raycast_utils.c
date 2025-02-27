/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeper <ezeper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:17 by ezeper            #+#    #+#             */
/*   Updated: 2025/02/27 19:35:16 by ezeper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_wall(int x, t_draw *draw, t_cub3d *cub)
{
	t_tex_draw	td;

	td.texture = cub->walls[draw->tex_num];
	td.step = 1.0 * 64 / draw->line_height;
	td.tex_pos = (draw->draw_start - HWINDOW / 2 + draw->line_height / 2) * td.step;
	td.img = mlx_new_image(cub->mlx, 1, HWINDOW);
	if (!td.img)
		return ;
	td.y = 0;
	while (td.y < HWINDOW)
	{
		if (td.y >= draw->draw_start && td.y < draw->draw_end)
		{
			td.tex_y = (int)td.tex_pos & 63;
			td.tex_pos += td.step;
			td.color = &td.texture->pixels[(td.tex_y * td.texture->width + draw->tex_x) * 4];
			td.pixel = &td.img->pixels[(td.y * td.img->width) * 4];
			td.i = 0;
			while (td.i < 4)
			{
				td.pixel[td.i] = td.color[td.i];
				td.i++;
			}
		}
		td.y++;
	}
	mlx_image_to_window(cub->mlx, td.img, x, 0);
}

void	perform_dda(t_ray *ray, t_cub3d *cub)
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
void	calculate_wall(t_ray *ray, t_draw *draw, t_cub3d *cub)
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
