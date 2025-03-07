/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:17 by ezeper            #+#    #+#             */
/*   Updated: 2025/03/07 12:57:28 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_color(mlx_texture_t *texture, int width, int tex_y, int tex_x)
{
	int				color;
	int				tex_index;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;

	tex_index = (tex_y * width + tex_x) * 4;
	b = texture->pixels[tex_index + 0];
	g = texture->pixels[tex_index + 1];
	r = texture->pixels[tex_index + 2];
	color = (r << 16) + (g << 8) + b;
	return (color);
}

void	draw_wall(int x, t_draw *draw, t_cub3d *cub)
{
	t_tex_draw	td;
	int			y;
	int			color;

	td.texture = cub->walls[draw->tex_num];
	td.step = 1.0 * 64 / draw->line_height;
	td.tex_pos = (draw->draw_start - HWINDOW / 2
			+ draw->line_height / 2) * td.step;
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		td.tex_y = (int)td.tex_pos & 63;
		td.tex_pos += td.step;
		color = get_color(td.texture, 64, td.tex_y, draw->tex_x);
		mlx_put_pixel(cub->bg_img, x, y, color);
		y++;
	}
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

int	norm_return(t_ray *ray)
{
	if (ray->step_y < 0)
		return (0);
	else
		return (1);
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
			draw->tex_num = 2;
		else
			draw->tex_num = 3;
	}
	else
		draw->tex_num = norm_return(ray);
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
