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

int main(int argc, char **argv)
{
    t_cub3d cub;

    ft_bzero(&cub, sizeof(t_cub3d));
    if (check_input(argc, argv)  != 0)
        return (1);
    if (check_map(argv[1]) != 0)
        return (1);
    ///@TODO: We need to initialize the game(MLX) and the map
    ///@TODO: I'm thinking about something like this:
    // if (init_game(&cub) != 0)
    //     return (1);
    ///@TODO: Then we'll need to start the loops(raycasting will need to be in a loop here too)
    ///@TODO: I'm thinking about something like this:
    // start_game(&cub);
    ///@TODO: After the program end we need to free everything used:
    // free_game(&cub);
    return (0);
}
