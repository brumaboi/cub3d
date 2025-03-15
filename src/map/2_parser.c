/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:02:30 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 16:02:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map(char *line, t_map *map)
{
	char	**new_map;
	size_t	old_size;
	size_t	new_size;
	size_t	i;

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

int	parse_line(char *line, t_map *map)
{
	char	*trimmed_line;
	char	*map_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
		return (printf("Error: Memory allocation failed\n"), 0);
	if (trimmed_line[0] == '\0')
		return (free(trimmed_line), 1);
	if (is_texture(trimmed_line))
	{
		if (!parse_texture(trimmed_line, map))
			return (free(trimmed_line), 0);
	}
	else if (is_color(trimmed_line))
	{
		if (!parse_color(trimmed_line, map))
			return (free(trimmed_line), 0);
	}
	else
	{
		map_line = ft_strtrim(line, "\n\r");
		parse_map(map_line, map);
		free(map_line);
	}
	return (free(trimmed_line), 1);
}
