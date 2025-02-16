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

static int	check_format(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension)
	{
		if (!ft_strncmp(extension, ".ber", 4))
			return (1);
	}
	return (0);
}

int check_input(int argc, char **argv)
{
    if (argc != 2)
        return(printf("Error: Invalid number of arguments\n"), 1);
    if (!check_format(argv[1]))
        return(printf("Error: Invalid file format\n"), 1);
    if (access(argv[1], F_OK) != 0)
        return(printf("Error: File does not exist\n"), 1);
    check_if_valid_map(argv[1]);
}

int main(int argc, char **argv)
{
    if (!check_input(agrc, argv))
        return (1);
    return (0);
}
