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
		if (!ft_strncmp(extension, ".cub", 4))
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
    return (0);
}

check_map(char *path)
{
    int fd;
    char *line;
    t_map map;

    ft_bzero(&map, sizeof(t_map));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Could not open file\n"), 1);
    line = get_next_line(fd);
    while (line > 0)
    {
        ///parsing logic
        line = get_next_line(fd);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_cub3d cub;

    ft_bzero(&cub, sizeof(t_cub3d));
    if (!check_input(agrc, argv))
        return (1);
    if (!check_map(argv[1], &cub))
        return (1);
    return (0);
}
