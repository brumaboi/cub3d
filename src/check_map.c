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

int parse_line(char *line, t_map *map)
{
    //trim empty lines
    char *trimmed_line;

    trimmed_line = ft_strtrim(line, " \t\n");
    if (!trimmed_line)
        return (printf("Error: Memory allocation failed\n"), 0);
    if (trimmed_line[0] == '\0')
        return (free(trimmed_line), 1);
    if (is_texture(trimmed_line)) //parse NO SO WE EA check format get texture
    {
        if (!parse_texture(trimmed_line, map))
            return (free(trimmed_line), 0);
    }
    else if (is_color(trimmed_line)) //parse F C get color
    {
        if (!parse_color(trimmed_line, map))
            return (free(trimmed_line), 0);
    }
    else  //store map lines after trimming everything(map doesn't need to be square)
    {
        if (!parse_map(trimmed_line, map))
            return (free(trimmed_line), 0);
    }
    free(trimmed_line);
    return(0);
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