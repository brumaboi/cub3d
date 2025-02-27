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

void free_game(t_cub3d *cub)
{
    int i;

    i = 0;
    while (i < 4)
    { 
        if (cub->walls[i])
           mlx_delete_texture(cub->walls[i]);           // Free textures
        i++;
    }
    if (cub->map.map)
    {
        i = 0;
        while (i < cub->map.rows)
        {
            free(cub->map.map[i]);
            i++;                       // Free map resources
            if (cub->map.map)
                free(cub->map.map);
        }
        free(cub->map.map);
    }
    free(cub->map.nord_texture);
    free(cub->map.south_texture); // Free texture paths
    free(cub->map.west_texture);
    free(cub->map.east_texture);
    mlx_terminate(cub->mlx); // and terminate the mlx
}

void   key_hook(mlx_key_data_t keydata, void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;
    if (keydata.action != MLX_PRESS)
        return ;
    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(cub->mlx);
    return ;
}

void game_loop(void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;
    raycaster(cub);
}

int start_game(t_cub3d *cub)
{
    mlx_loop_hook(cub->mlx, game_loop, cub);
    mlx_key_hook(cub->mlx, key_hook, cub);
    mlx_loop(cub->mlx);
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
    if (init_game(&cub) != 0)
        return (1);
    if (start_game(&cub) != 0)
        return (1);
    ///@TODO: After the program end we need to free everything used:
    // free_game(&cub);
    return (0);
}
