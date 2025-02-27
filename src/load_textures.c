/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakemrezeper <burakemrezeper@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:59:04 by burakemreze       #+#    #+#             */
/*   Updated: 2025/02/27 21:00:46 by burakemreze      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int load_textur(t_cub3d *cub)
{
    int i;

    i = 0;
        cub->walls[0] = mlx_load_png(cub->map.nord_texture);
        cub->walls[1] = mlx_load_png(cub->map.south_texture);
        cub->walls[2] = mlx_load_png(cub->map.west_texture);
        cub->walls[3] = mlx_load_png(cub->map.east_texture);
        
        while(i < 4)// Check if any texture failed to load
        {
            if (!cub->walls[i])
                return (1);
            i++;
        }
}