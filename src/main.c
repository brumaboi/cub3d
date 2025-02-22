/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:43:06 by marvin            #+#    #+#             */
/*   Updated: 2025/02/16 13:43:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int load_walls(t_cub3d *cub)
{
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
    printf("DEBUG: Loaded north texture from: %s (ptr: %p)\n", cub->map.nord_texture, cub->walls[0]);
    printf("DEBUG: Loaded south texture from: %s (ptr: %p)\n", cub->map.south_texture, cub->walls[1]);
    printf("DEBUG: Loaded west texture from: %s (ptr: %p)\n", cub->map.west_texture, cub->walls[2]);
    printf("DEBUG: Loaded east texture from: %s (ptr: %p)\n", cub->map.east_texture, cub->walls[3]);
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

int init_game(t_cub3d *cub)
{
    cub->mlx = mlx_init(WWINDOW, HWINDOW, "Cub3D", false);
    if (!cub->mlx)
        return (printf("Error: mlx_init failed\n"), 1);
    draw_background(cub);
    if (load_walls(cub) != 0)
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_cub3d cub;

    ft_bzero(&cub, sizeof(t_cub3d));
    if (check_input(argc, argv)  != 0)
        return (1);
    if (check_map(argv[1], &cub.map) != 0)
        return (1);
    ///@TODO: We need to initialize the game(MLX) and the map
    if (init_game(&cub) != 0)
        return (1);
    ///@TODO: Then we'll need to start the loops(raycasting will need to be in a loop here too)
    ///@TODO: I'm thinking about something like this:
    // start_game(&cub);
    ///@TODO: After the program end we need to free everything used:
    // free_game(&cub);
    mlx_loop(cub.mlx);
    return (0);
}
