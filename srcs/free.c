/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:17:14 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 17:12:56 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_hole(t_list *head, t_map *map, int *path)
{
	free_lines(head);
	free_map(map);
	free_path(path);
	return (0);
}

int			free_path(int *path)
{
	if (path)
		ft_memdel((void **)&path);
	return (1);
}

void		free_connections(t_map *map)
{
	int		y;

	if (!(map->connections))
		return ;
	y = 0;
	while (y < map->room_nb)
	{
		if (map->connections[y])
			ft_memdel((void **)&map->connections[y]);
		y++;
	}
	if (map->connections)
		ft_memdel((void **)&map->connections);
}

int			free_map(t_map *map)
{
	t_room	*room;
	t_room	*next_room;

	room = map->rooms;
	while (room)
	{
		next_room = room->next;
		if (room->name)
			ft_strdel(&room->name);
		if (room)
			ft_memdel((void **)&room);
		room = next_room;
	}
	free_connections(map);
	if (map)
		ft_memdel((void **)&map);
	return (1);
}

int			free_lines(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->content)
			ft_memdel(&current->content);
		if (current)
			ft_memdel((void **)&current);
		current = next;
	}
	return (1);
}
