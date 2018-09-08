/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:47:48 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 14:47:49 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			connect_rooms(t_map *map, t_room *room1, t_room *room2)
{
	map->connections[room1->id][room2->id] = 1;
	map->connections[room2->id][room1->id] = 1;
	return (1);
}

int			alloc_room(t_map *map, char *str, t_room *new)
{
	if (room_exists(map, get_room_name(str)) != NULL)
		return (0);
	if (!(map->rooms))
	{
		if (!(map->rooms = (t_room *)malloc(sizeof(t_room))))
			return (0);
		map->last = map->rooms;
	}
	else
	{
		if (!(new = (t_room *)malloc(sizeof(t_room))))
			return (0);
		map->last->next = new;
		map->last = new;
	}
	return (1);
}

int			handle_hashtag(t_map *map, char *str, int *modifier)
{
	if (str[0] == '#' && str[1] == '#')
	{
		if (ft_strcmp(str + 2, "start") == 0)
		{
			if (map->start == NULL)
				*modifier = 1;
			else
				return (0);
		}
		else if (ft_strcmp(str + 2, "end") == 0)
		{
			if (map->end == NULL)
				*modifier = 2;
			else
				return (0);
		}
	}
	return (1);
}

int			handle_room(t_map *map, char *str, int *modifier)
{
	t_room	*new;

	new = NULL;
	if (!(alloc_room(map, str, new)))
		return (0);
	map->last->next = NULL;
	map->last->name = get_room_name(str);
	map->last->id = map->room_nb;
	map->last->ant_nb = 0;
	if (((map->last->x = get_room_coords(str, 1)) == -1)
			|| ((map->last->y = get_room_coords(str, 2)) == -1))
		return (0);
	if (!(is_coords_available(map, map->last->x, map->last->y)))
		return (0);
	map->last->visited = 0;
	if (*modifier != 0)
	{
		if (*modifier == 1)
			map->start = map->last;
		else if (*modifier == 2)
			map->end = map->last;
		*modifier = 0;
	}
	(map->room_nb)++;
	return (1);
}
