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

#include "../inc/cub3d.h"

void parse_line(char *line, t_map *map)
{
    //trim empty lines
    char *trimmed_line;

    trimmed_line = ft_strtrim(line, " \t\n");
    if (!trimmed_line)
        return (printf("Error: Memory allocation failed\n"), 0);
    if (trimmed_line[0] == '\0')
        return (free(trimmed_line), 1);
    //parse NO SO WE EA check format get texture
    //parse F C get color
    //store map lines after trimming everything(map doesn't need to be square)
    //then we need to check the new_map for: invalid characters, map rules, player position and view direction
}

check_map(char *path)
{
    int fd;
    char *line;
    t_map map;

    ft_bzero(&map, sizeof(t_map));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Could not open file\n"), 1);
    line = get_next_line(fd);
    while (line > 0)
    {
        if (!parse_line(line, &map))
            return (1);
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}