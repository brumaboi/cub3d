/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:05:01 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/15 17:12:13 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static void	get_bounds(const char *row, int *start, int *end)
{
	int	i;

	i = ft_strlen(row);
	*start = 0;
	while (*start < i && ft_isspace(row[*start]))
		(*start)++;
	*end = i - 1;
	while (*end >= 0 && ft_isspace(row[*end]))
		(*end)--;
}

int	check_bounds(t_map *map)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (ft_strlen(map->map[i]) == 0)
			return (printf("Error: Empty row in map\n"), 1);
		if (i != 0 && i != map->rows -1)
		{
			get_bounds(map->map[i], &start, &end);
			if (start > end)
				return (printf("Error: No valid characters\n"), 1);
			if (map->map[i][start] != WALL)
				return (printf("Error: Row doesn't start with a wall\n"), 1);
			if (map->map[i][end] != WALL)
				return (printf("Error: Row doesn't end with a wall\n"), 1);
		}
		i++;
	}
	return (0);
}

void	save_player_data(t_map *map, int elem, int i, int j)
{
	map->player_pos.x = j + 0.001;
	map->player_pos.y = i + 0.001;
	if (elem == 'N')
		map->player = 0;
	else if (elem == 'S')
		map->player = 1;
	else if (elem == 'W')
		map->player = 2;
	else if (elem == 'E')
		map->player = 3;
}

int	process_element(t_map *map, int i, int j, int *player_count)
{
	int	elem;

	elem = map->map[i][j];
	if (elem != WALL && elem != FLOOR && elem != ' '
		&& elem != 'N' && elem != 'S' && elem != 'E' && elem != 'W')
		return (printf("Error: Invalid element found\n"), 1);
	if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
	{
		(*player_count)++;
		save_player_data(map, elem, i, j);
	}
	return (0);
}

int	check_elements(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (process_element(map, i, j, &player_count))
				return (1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error: Wrong number of players\n"), 1);
	return (0);
}
