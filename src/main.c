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

void clear_screen(t_cub3d *cub)
{
    int x;
    int y;

    if (cub->bg_img)
        mlx_delete_image(cub->mlx, cub->bg_img);
    cub->bg_img = mlx_new_image(cub->mlx, WWINDOW, HWINDOW);
    if (!cub->bg_img)
    {
        printf("Error: Failed to create new image\n");
        return;
    }
    y = 0;
    while (y < HWINDOW)
    {
        x = 0;
        while (x < WWINDOW)
        {
            if (y < HWINDOW / 2)
                mlx_put_pixel(cub->bg_img, x, y, cub->map.ceiling_color);
            else
                mlx_put_pixel(cub->bg_img, x, y, cub->map.floor_color);
            x++;
        }
        y++;
    }
}

void handle_input(t_cub3d *cub)
{
    cub->player.input_forward      = mlx_is_key_down(cub->mlx, MLX_KEY_W);
    cub->player.input_backward     = mlx_is_key_down(cub->mlx, MLX_KEY_S);
    cub->player.input_strafe_left  = mlx_is_key_down(cub->mlx, MLX_KEY_A);
    cub->player.input_strafe_right = mlx_is_key_down(cub->mlx, MLX_KEY_D);
    cub->player.input_rotate_left  = mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT);
    cub->player.input_rotate_right = mlx_is_key_down(cub->mlx, MLX_KEY_LEFT);
}

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

void update_player(t_cub3d *cub)
{
    double move_speed;

    move_speed = cub->player.walk_speed;
    update_forward(cub, move_speed);
    update_backward(cub, move_speed);
    // update_strafe_left(cub, move_speed);
    // update_strafe_right(cub, move_speed);
    // update_rotate_left(cub);
    // update_rotate_right(cub);
}

void game_loop(void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;

    handle_input(cub);
    update_player(cub);
    clear_screen(cub);
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
