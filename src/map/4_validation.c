/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_validation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:42:21 by sbruma            #+#    #+#             */
/*   Updated: 2025/02/18 15:56:47 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int is_walkable(char c)
{
    return (c == FLOOR || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int check_touch(t_map *map, int i, int j)
{
    int di;
    int dj;
    int ni;
    int nj;
    int neighbor_len;

    di = -1;
    while (di <= 1)
    {
        dj = -1;
        while (dj <= 1)
        {
            ni = i + di;
            nj = j + dj;
            if (ni < 0 || ni >= map->rows)
                return(printf("Error: Walkable touches the void\n"), 1);
            neighbor_len = ft_strlen(map->map[ni]);
            if (nj < 0 || nj >= neighbor_len)
                return(printf("Error: Walkable touches the void\n"), 1);
            if (map->map[ni][nj] == ' ')
                return(printf("Error: Walkable touches the void\n"), 1);
            dj++;
        }
        di++;
    }
    return (0);
}

int check_surroundings(t_map *map)
{
    int i;
    int j;
    int row_len;
    char cell;
    
    i = 0;
    while (i < map->rows)
    {
        row_len = ft_strlen(map->map[i]);
        j = 0;
        while (j < row_len)
        {
            cell = map->map[i][j];
            if (is_walkable(cell))
            {
                //vertical, horizontal, diagonal surrounding check logic
                if(check_touch(map, i, j) == 1)
                    return(1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

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

int check_elements(t_map *map)
{
    int i;
    int j;
    int player_count;
    int elem;

    player_count = 0;
    i = 0;
    while (i < map->rows)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            elem = map->map[i][j];
            if (elem != WALL && elem != FLOOR && elem != ' '
                && elem != 'N' && elem != 'S' && elem != 'E' && elem != 'W')
                return(printf("Error: Invalid element found\n"), 1);
            if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
            {
                player_count++;
                map->player_pos.x = j;
                map->player_pos.y = i;
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (printf("Error: Wrong number of players\n"), 1);
    return (0);
}

int validate_map(t_map *map)
{   
    if (check_elements(map) == 1)
        return(0);
    if(check_bounds(map) == 1)
        return (0);
    if (check_surroundings(map) == 1)
        return(0);
    // check_player_mobility(map);
    return (1);
}
