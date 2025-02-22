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
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WALL '1'
# define FLOOR '0'

# define WWINDOW 800
# define HWINDOW 600

typedef struct s_pos
{
    double x;
    double y;
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
}   t_map;

typedef struct s_player
{
    t_pos   pos;
    t_pos   dir;
    t_pos   plane;
    int     turn_direction;
    int     walk_direction;
    double  rotation_angle;
    double  walk_speed;
    double  turn_speed;
}   t_player;

typedef struct s_cub3d
{
    mlx_t       *mlx;
    void        *win;
    void        *img;
    mlx_texture_t *walls[4];
    mlx_image_t *bg_img;
    t_map       map;
    t_player    player;
}   t_cub3d;

//map
//config
int is_texture(char *line);
void parse_texture(char *line, t_map *map);
int is_color(char *line);
void parse_color(char *line, t_map *map);
//parser
int parse_line(char *line, t_map *map);
void parse_map(char *line, t_map *map);
//checker_map
int check_map(char *path, t_map *map);
//validation
int validate_map(t_map *map);
int check_elements(t_map *map);
int check_bounds(t_map *map);
int check_surroundings(t_map *map);
int is_walkable(char c);
int check_player_mobility(t_map *map);

int check_input(int argc, char **argv);
int	check_format(char *path, char *format);

#endif