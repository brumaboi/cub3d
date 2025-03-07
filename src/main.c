/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:43:06 by marvin            #+#    #+#             */
/*   Updated: 2025/02/16 13:43:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	print_start();
	ft_bzero(&cub, sizeof(t_cub3d));
	if (check_input(argc, argv) != 0)
		return (1);
	if (check_map(argv[1], &cub.map) != 0)
		return (1);
	if (init_game(&cub) != 0)
		return (1);
	if (start_game(&cub) != 0)
		return (1);
	// free_game(&cub);
	return (print_end(), 0);
}
