/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:23:07 by marvin            #+#    #+#             */
/*   Updated: 2025/02/22 10:23:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int load_walls(t_cub3d *cub)
{
    int i;

    i = 0;
    cub->walls[0] = mlx_load_png(cub->map.nord_texture);
    if (!cub->walls[0])
        return (printf("Error: Failed to load texture: %s\n", cub->map.nord_texture), 1);
    cub->walls[1] = mlx_load_png(cub->map.south_texture);
    if (!cub->walls[1])
        return (printf("Error: Failed to load texture: %s\n", cub->map.south_texture), 1);
    cub->walls[2] = mlx_load_png(cub->map.west_texture);
    if (!cub->walls[2])
        return (printf("Error: Failed to load texture: %s\n", cub->map.west_texture), 1);
    cub->walls[3] = mlx_load_png(cub->map.east_texture);
    if (!cub->walls[3])
        return (printf("Error: Failed to load texture: %s\n", cub->map.east_texture), 1);
    while (i < 4)
    {
        if (!cub->walls[i])
            return (1);
        i++;
    }
    return (0);
}

void draw_background(t_cub3d *cub)
{
    int i;
    int j;

    cub->bg_img = mlx_new_image(cub->mlx, WWINDOW, HWINDOW);
    if (!cub->bg_img)
    {
        printf("Error: Failed to create background image\n");
        return;
    }
    i = 0;
    while (i < HWINDOW)
    {
        j = 0;
        while (j < WWINDOW)
        {
            if (i < HWINDOW / 2)
                mlx_put_pixel(cub->bg_img, j, i, cub->map.ceiling_color);
            else
                mlx_put_pixel(cub->bg_img, j, i, cub->map.floor_color);
            j++;
        }
        i++;
    }
    mlx_image_to_window(cub->mlx, cub->bg_img, 0, 0);
}

int init_player(t_cub3d *cub)
{
    cub->player.pos.x = cub->map.player_pos.x;
    cub->player.pos.y = cub->map.player_pos.y;
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
    else if(cub->map.player == 2)
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
    cub->player.walk_speed = 0.05;
    cub->player.turn_speed = 0.05;
    return (0);
}

int init_game(t_cub3d *cub)
{
    cub->mlx = mlx_init(WWINDOW, HWINDOW, "Cub3D", false);
    if (!cub->mlx)
        return (printf("Error: mlx_init failed\n"), 1);
    draw_background(cub);
    if (load_walls(cub) != 0)
        return (printf("Error: failed to load walls\n"), 1);
    if (init_player(cub) != 0)
        return (printf("Error: failed to init player\n"), 1);
    return (0);
}
