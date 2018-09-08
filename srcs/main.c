/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 18:51:56 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 17:32:25 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					ft_error(char *error)
{
	ft_dprintf(2, "%s\n", error);
	return (EXIT_FAILURE);
}

int					dfs(t_map *map, t_room *room, int **path, int depth)
{
	int				i;
	t_room			*current;
	int				res;

	i = 0;
	room->visited = 1;
	if (room->id == map->end->id)
		return (depth);
	while (i < map->room_nb)
	{
		if (map->connections[room->id][i])
		{
			(*path)[depth] = i;
			current = get_room_from_id(map, i);
			if (current->visited == 0)
			{
				if ((res = dfs(map, current, path, ++depth)))
					return (res);
				current->visited = 0;
				depth--;
			}
		}
		i++;
	}
	return (0);
}

int					main(void)
{
	t_list			*head;
	t_map			*map;
	int				*path;
	int				path_len;

	head = NULL;
	if (!(parse_file(&head)))
		return (free_lines(head) && ft_error("Error"));
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (ft_error("Error"));
	if (!(parse_map(map, head)))
		return (free_lines(head) && free_map(map) && ft_error("Error"));
	if (!(path = (int *)malloc((map->room_nb + 1) * sizeof(int))))
		return (free_lines(head) && free_map(map)
			&& free_path(path) && ft_error("Error"));
	ft_bzero(path, map->room_nb + 1);
	if (!(path_len = dfs(map, map->start, &path, 0)))
		return (free_lines(head) && free_map(map)
			&& free_path(path) && ft_error("Error"));
	print_header(map);
	send_ants(map, path, path_len);
	return (free_hole(head, map, path));
}
