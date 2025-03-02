/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_update_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:23:19 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/03 13:18:24 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int check_hit(t_cub3d *cub, double x, double y)
{
    int map_x;
    int map_y;
    
    map_x = (int)x;
    map_y = (int)y;
    if (map_y < 0 || map_y >= cub->map.rows || map_x < 0 || map_x >= cub->map.columns)
        return (0);
    return (is_walkable(cub->map.map[map_y][map_x]));
}

void update_forward(t_cub3d *cub, double move_speed)
{
    double new_x;
    double new_y;

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

void update_backward(t_cub3d *cub, double move_speed)
{
    double new_x;
    double new_y;

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

void update_left(t_cub3d *cub, double move_speed)
{
    double new_x;
    double new_y;

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

void update_right(t_cub3d *cub, double move_speed)
{
    double new_x;
    double new_y;

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

void update_rotate_left(t_cub3d *cub)
{
    double old_dir_x;
    double old_plane_x;

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

void update_rotate_right(t_cub3d *cub)
{
    double old_dir_x;
    double old_plane_x;

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

void update_player(t_cub3d *cub)
{
    double move_speed;

    move_speed = cub->player.walk_speed;
    update_forward(cub, move_speed);
    update_backward(cub, move_speed);
    update_left(cub, move_speed);
    update_right(cub, move_speed);
    update_rotate_left(cub);
    update_rotate_right(cub);
}
