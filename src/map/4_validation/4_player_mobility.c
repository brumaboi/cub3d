/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_player_mobility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:11:31 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/05 13:48:11 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static void	check_above(t_map *map, int i, int j, int *can_move)
{
	int	ni;
	int	nj;
	int	row_len;

	ni = i - 1;
	nj = j;
	if (ni >= 0)
	{
		row_len = ft_strlen(map->map[ni]);
		if (nj < row_len && is_walkable(map->map[ni][nj]))
			*can_move = 1;
	}
}

static void	check_below(t_map *map, int i, int j, int *can_move)
{
	int	ni;
	int	nj;
	int	row_len;

	ni = i + 1;
	nj = j;
	if (!*can_move && ni < map->rows)
	{
		row_len = ft_strlen(map->map[ni]);
		if (nj < row_len && is_walkable(map->map[ni][nj]))
			*can_move = 1;
	}
}

static void	check_left(t_map *map, int i, int j, int *can_move)
{
	int	ni;
	int	nj;
	int	row_len;

	ni = i;
	nj = j - 1;
	if (!*can_move && nj >= 0)
	{
		row_len = ft_strlen(map->map[ni]);
		if (nj < row_len && is_walkable(map->map[ni][nj]))
			*can_move = 1;
	}
}

static void	check_right(t_map *map, int i, int j, int *can_move)
{
	int	ni;
	int	nj;
	int	row_len;

	ni = i;
	nj = j + 1;
	if (!*can_move)
	{
		row_len = ft_strlen(map->map[ni]);
		if (nj < row_len && is_walkable(map->map[ni][nj]))
			*can_move = 1;
	}
}

int	check_player_mobility(t_map *map)
{
	int	i;
	int	j;
	int	can_move;

	i = map->player_pos.y;
	j = map->player_pos.x;
	can_move = 0;
	check_above(map, i, j, &can_move);
	check_below(map, i, j, &can_move);
	check_left(map, i, j, &can_move);
	check_right(map, i, j, &can_move);
	if (!can_move)
		return (printf("Error: Player is completely isolated by walls\n"), 1);
	return (0);
}
