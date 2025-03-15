/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_validate_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:42:21 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/15 15:18:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int check_config(t_map *map)
{
	int tmp;

	tmp = 0;

	if (!map->nord_texture || !map->south_texture || !map->west_texture || !map->east_texture)
	{
		printf("Error: Missing texture path\n");
		tmp = 1;
	}
	if (map->floor_color == -1 || map->ceiling_color == -1)
	{
		printf ("Error: Missing floor or ceiling color\n");
		tmp = 1;
	}
	return (tmp);
}

int	validate_map(t_map *map)
{
	if (check_config(map) == 1)
		return (0);
	if (check_elements(map) == 1)
		return (0);
	if (check_bounds(map) == 1)
		return (0);
	if (check_surroundings(map) == 1)
		return (0);
	if (check_player_mobility(map) == 1)
		return (0);
	return (1);
}
