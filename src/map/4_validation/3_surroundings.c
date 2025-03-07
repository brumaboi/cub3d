/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surroundings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:05:32 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/07 13:46:01 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_walkable(char c)
{
	return (c == FLOOR || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_touch(t_map *map, int i, int j)
{
	int	di;
	int	dj;
	int	ni;
	int	nj;
	int	neighbor_len;

	di = -1;
	while (di <= 1)
	{
		dj = -1;
		while (dj <= 1)
		{
			ni = i + di;
			nj = j + dj++;
			if (ni < 0 || ni >= map->rows)
				return (printf("Error: Walkable touches the void\n"), 1);
			neighbor_len = ft_strlen(map->map[ni]);
			if (nj < 0 || nj >= neighbor_len)
				return (printf("Error: Walkable touches the void\n"), 1);
			if (map->map[ni][nj] == ' ')
				return (printf("Error: Walkable touches the void\n"), 1);
		}
		di++;
	}
	return (0);
}

int	check_surroundings(t_map *map)
{
	int		i;
	int		j;
	int		row_len;
	char	cell;

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
				if (check_touch(map, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
