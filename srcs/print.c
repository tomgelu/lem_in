/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:37:40 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 17:29:23 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		send_to_path(t_map *map, int *path, int path_len, t_ant *ant)
{
	int		i;
	t_room	*next;

	i = path_len - 1;
	while (i >= 0 && ant->room->id != map->end->id)
	{
		if (ant->room->id == map->start->id
				|| ant->room->id == path[i])
		{
			next = (ant->room->id == map->start->id)
				? get_room_from_id(map, path[0])
				: get_room_from_id(map, path[i + 1]);
			if (next->ant_nb == 0 || next->id == map->end->id)
			{
				ft_printf("L%d-%s ", ant->id, next->name);
				ant->room->ant_nb -= 1;
				ant->room = next;
				ant->room->ant_nb += 1;
				break ;
			}
		}
		i--;
	}
}

void		send_ants(t_map *map, int *path, int path_len)
{
	t_ant	**ants;
	int		ant;

	if (!(ants = alloc_and_init_ants(map)))
		return ;
	while (map->end->ant_nb != map->ant_pop)
	{
		ant = 0;
		while (ant < map->ant_pop)
		{
			send_to_path(map, path, path_len, ants[ant]);
			ant++;
		}
		ft_printf("\n");
	}
	free_ants(ants, map->ant_pop);
}

void		print_rooms(t_map *map, t_room *room)
{
	while (room)
	{
		if (room->id == map->start->id)
			ft_printf("##start\n");
		if (room->id == map->end->id)
			ft_printf("##end\n");
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
	}
}

void		print_header(t_map *map)
{
	t_room	*room;
	t_room	*room2;
	int		i;
	int		j;

	ft_printf("%d\n", map->ant_pop);
	room = map->rooms;
	print_rooms(map, room);
	i = 0;
	while (i < map->room_nb)
	{
		room = get_room_from_id(map, i);
		j = 0;
		while (j < map->room_nb)
		{
			room2 = get_room_from_id(map, j);
			if (map->connections[i][j] && i < j)
				ft_printf("%s-%s\n", room->name, room2->name);
			j++;
		}
		i++;
	}
	ft_printf("\n");
}
