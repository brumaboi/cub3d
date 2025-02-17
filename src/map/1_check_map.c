/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:05:20 by marvin            #+#    #+#             */
/*   Updated: 2025/02/16 23:05:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int check_map(char *path)
{
    int fd;
    char *line;
    t_map map;

    ft_bzero(&map, sizeof(t_map));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Could not open file\n"), 1);
    line = get_next_line(fd);
    while (line != 0)
    {
        if (!parse_line(line, &map))
            return (1);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    // if (!validate_map(&map)) //then we need to check the new_map for: invalid characters, map rules, player position and view direction
    //     return (1);
    return (0);
}