/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:43:10 by marvin            #+#    #+#             */
/*   Updated: 2025/02/16 13:43:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_cub3d
{
    mlx_t       *mlx;
    mlx_win_t   *win;
    mlx_img_t   *img;
    t_map       map;
    t_player    player;
}   t_cub3d;

typedef struct s_player
{
    t_pos   pos;
    int     direction;
    int     turn_direction;
    int     walk_direction;
    double  rotation_angle;
    double  walk_speed;
    double  turn_speed;
}   t_player;

typedef struct s_pos
{
    int x;
    int y;
}   t_pos;

typedef struct s_map
{
    char    **map;
    int     rows;
    int     columns;
    int     player;
    t_pos   player_pos;
    int     initial_render;
    char   *nord_texture;
    char   *south_texture;
    char   *west_texture;
    char   *east_texture;
    int    floor_color;
    int    ceiling_color;
    mlx_t  *mlx;
}   t_map;

#endif