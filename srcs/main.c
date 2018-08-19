/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 18:51:56 by tgelu             #+#    #+#             */
/*   Updated: 2018/08/19 22:14:35 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*get_room_from_id(t_map *map, int id)
{
	t_room	*current;

	current = map->rooms;
	while (current)
	{
		if (current->id == id)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int		DFS(t_map *map, t_room *room, int **path, int depth)
{
	int		i;
	t_room	*current;

	i = 0;
	room->visited = 1;
	if (room->id == map->end->id)
		return (1);
	while (i < map->room_nb)
	{
		if (map->connections[room->id][i])
		{
			(*path)[depth] = i;
			current = get_room_from_id(map, i);
			if (current->visited == 0)
				if (DFS(map, current, path, ++depth))
					return (1);
		}
		i++;
	}
	return (0);
}

int		ft_error(char *error)
{
	ft_printf("%s\n", error);
	return (EXIT_FAILURE);
}

void	send_ants(t_map *map, int *path)
{
	t_ant	*ants;
	int		i;

	ants = (t_ant *)malloc(sizeof(t_ant) * (map->ant_pop + 1));
	while (i < map->ant_pop)
	{
		ants[i].room = map->start;
		i++;
	}
}

int		main(int ac, char **av)
{
	t_list			*head;
	t_list			*next;
	t_map			*map;
	int				*path;

	(void)ac;
	(void)av;
	head = NULL;
	if (!(parse_file(&head)))
		return (ft_error("Error"));
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (ft_error("Error"));
	if (!(parse_map(map, head)))
		return (ft_error("Error"));
	path = ft_memalloc(map->room_nb + 1);
	if (!(DFS(map, map->start, &path, 0)))
		return (ft_error("Error"));
	send_ants(map, path);
	ft_memdel((void **)&map);
	while (head)
	{
		next = head->next;
		ft_strdel((char **)&(head->content));
		ft_memdel((void **)&head);
		head = next;
	}
	return (0);
}
