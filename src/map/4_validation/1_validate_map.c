/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_validate_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:42:21 by sbruma            #+#    #+#             */
/*   Updated: 2025/02/18 16:08:38 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

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
