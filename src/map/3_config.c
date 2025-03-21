/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 16:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_texture(char *line)
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

int	parse_texture(char *line, t_map *map)
{
	char	*path;

	path = ft_strtrim(line + 2, " \t\n");
	if (!path)
		return (0);
	if (!check_format(path, ".png"))
	{
		printf("Error: Invalid texture format\n");
		return (free(path), 0);
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
		return (free(path), 0);
	}
	return (1);
}

int	is_color(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	right_color(char *line, char **rgb, t_map *map)
{
	int		r;
	int		g;
	int		b;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
	{
		printf("Error: Invalid color\n");
		return (free(*rgb), 0);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error: Invalid color\n");
		return (free(*rgb), 0);
	}
	free(rgb);
	if (ft_strncmp(line, "F ", 2) == 0)
		map->floor_color = (r << 24) + (g << 16) + (b << 8) + 0xFF;
	else
		map->ceiling_color = (r << 24) + (g << 16) + (b << 8) + 0xFF;
	return (1);
}

int	parse_color(char *line, t_map *map)
{
	char	**rgb;
	char	*color;

	color = ft_strtrim(line + 1, " \t\n");
	if (!color)
		return (0);
	rgb = ft_split(color, ',');
	free(color);
	if (!*rgb)
		return (0);
	return (right_color(line, rgb, map));
}
