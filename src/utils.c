/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruma <sbruma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:05:03 by sbruma            #+#    #+#             */
/*   Updated: 2025/03/14 19:03:11 by sbruma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_game(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->walls[i])
			mlx_delete_texture(cub->walls[i++]);
	}
	if (cub->map.map)
	{
		i = 0;
		while (i < cub->map.rows)
		{
			free(cub->map.map[i]);
			i++;
			if (cub->map.map)
				free(cub->map.map);
		}
		free(cub->map.map);
	}
	free(cub->map.nord_texture);
	free(cub->map.south_texture);
	free(cub->map.west_texture);
	free(cub->map.east_texture);
	mlx_terminate(cub->mlx);
}

void	print_start(void)
{
	printf("\033[H\033[J");
	printf("\n");
	printf("\033[32m");
	printf(" ██████╗  █████╗ ███╗   ███╗███████╗   ██████╗ ███╗   ██╗\n");
	printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝  ██╔═══██╗████╗  ██║\n");
	printf("██║  ███╗███████║██╔████╔██║█████╗    ██║   ██║██╔██╗ ██║\n");
	printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝    ██║   ██║██║╚██╗██║\n");
	printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗  ╚██████╔╝██║ ╚████║\n");
	printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝   ╚═════╝ ╚═╝  ╚═══╝\n");
	printf("\033[0m");
}

void	print_end(int clear)
{
	if (clear == 0)
		printf("\033[H\033[J");
	printf("\n");
	printf("\033[91m");
	printf(" ██████╗  █████╗ ███╗   ███╗███████╗   ██████╗ ███████╗███████╗\n");
	printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝  ██╔═══██╗██╔════╝██╔════╝\n");
	printf("██║  ███╗███████║██╔████╔██║█████╗    ██║   ██║█████╗  █████╗  \n");
	printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝    ██║   ██║██╔══╝  ██╔══╝  \n");
	printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗  ╚██████╔╝██║     ██║     \n");
	printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝   ╚═════╝ ╚═╝     ╚═╝     \n");
	printf("\033[0m");
}
