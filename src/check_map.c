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

int is_texture(char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (1);
    if (ft_strncmp(line, "SO ", 3) == 0)
        return (1);
    if (ft_strncmp(line, "WE ", 3) == 0)
        return (1);
    if (ft_strncmp(line, "EA ", 3) == 0)
        return (1);
    return (0);
}

void parse_texture(char *line, t_map *map)
{   
    char *path;

    path = ft_strtrim(line + 2, " \t\n");
    if (!path)
        return ;
    if (!check_format(path, ".png"))
    {
        printf("Error: Invalid texture format\n");
        free(path);
        return ;
    }
    if (ft_strncmp(line, "NO ", 3) == 0 && !map->nord_texture)
        map->nord_texture = path;
    else if (ft_strncmp(line, "SO ", 3) == 0 && !map->south_texture)
        map->south_texture = path;
    else if (ft_strncmp(line, "WE ", 3) == 0 && !map->west_texture)
        map->west_texture = path;
    else if (ft_strncmp(line, "EA ", 3) == 0 && !map->east_texture)
        map->east_texture = path;
    else
    {
        printf("Error: Duplicate texture\n");
        free(path);
    }
}

int is_color(char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
        return (1);
    if (ft_strncmp(line, "C ", 2) == 0)
        return (1);
    return (0);
}

void parse_color(char *line, t_map *map)
{
    char    **rgb;
    char    *color;
    int     r;
    int     g;
    int     b;

    color = ft_strtrim(line + 1, " \t\n");
    if (!color)
        return ;
    rgb = ft_split(color, ',');
    free(color);
    if (!*rgb)
        return ;
    if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
    {
        printf("Error: Invalid color\n");
        free(*rgb);
        return ;
    }
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error: Invalid color\n");
        free(*rgb);
        return ;
    }
    free(*rgb);
    if (ft_strncmp(line, "F ", 2) == 0)
        map->floor_color = (r << 16) + (g << 8) + b;
    else
        map->ceiling_color = (r << 16) + (g << 8) + b;
}

void parse_map(char *line, t_map *map)
{
    char **new_map;
    size_t old_size;
    size_t new_size;
    size_t i;

    old_size = (map->rows + 1) * sizeof(char *);
    new_size = (map->rows + 2) * sizeof(char *);
    new_map = (char **)ft_realloc(map->map, old_size, new_size);
    if (!new_map)
        return ;
    new_map[map->rows] = ft_strdup(line);
    if (!new_map[map->rows])
        return ;
    new_map[map->rows + 1] = NULL;
    map->map = new_map;
    map->rows++;
    i = ft_strlen(line);
    if (i > (size_t)map->columns)
        map->columns = i;
}

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
        parse_texture(trimmed_line, map);
    else if (is_color(trimmed_line)) //parse F C get color
        parse_color(trimmed_line, map);
    else  //store map lines after trimming everything
    {
        parse_map(trimmed_line, map);
    }
    free(trimmed_line);
    debug_print_map(map);
    return(1);
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
    // if (!validate_map(&map)) //then we need to check the new_map for: invalid characters, map rules, player position and view direction
    //     return (1);
    return (0);
}