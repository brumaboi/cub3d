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

static void get_bounds(const char *row, int *start, int *end)
{
    int i;

    i = ft_strlen(row);
    *start = 0;
    while (*start < i && ft_isspace(row[*start]))
        (*start)++;
    *end = i - 1;
    while (*end >= 0 && ft_isspace(row[*end]))
        (*end)--;
}

int check_bounds(t_map *map)
{
    int start;
    int end;
    int i;

    i = 0;
    while (i < map->rows)
    {
        if (ft_strlen(map->map[i]) == 0)
            return (printf("Error: Empty row in map\n"), 1);
        if (i != 0 && i != map->rows -1)
        {
            get_bounds(map->map[i], &start, &end);
            if (start > end)
                return(printf("Error: No valid characters\n"), 1);
            if (map->map[i][start] != WALL)
                return(printf("Error: Row doesn't start with a wall\n"), 1);
            if (map->map[i][end] != WALL)
                return(printf("Error: Row doesn't end with a wall\n"), 1);

        }
        i++;
    }
    return(0);
}

int validate_map(t_map *map)
{   
    if(check_bounds(map) == 1)
        return (0);
    // check_elements(map);
    // check_neighbors(map);
    // check_player_mobility(map);
    return (1);
}

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
    if (!validate_map(&map)) //then we need to check the new_map for: invalid characters, map rules, player position and view direction
        return (1);
    return (0);
}