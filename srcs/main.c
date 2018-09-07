/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 18:51:56 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/05 15:31:17 by tgelu            ###   ########.fr       */
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
	int		res;

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
				if ((res = DFS(map, current, path, ++depth)))
					return (res);
				room->visited = 0;
			}
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

void	send_ants(t_map *map, int *path, int path_len)
{
	t_ant	**ants;
	t_room	*next;
	int		i;
	int		ant;

	i = 0;
	map->start->ant_nb = map->ant_pop;
	ants = (t_ant **)malloc(sizeof(t_ant *) * (map->ant_pop + 1));
	while (i < map->ant_pop)
	{
		ants[i] = ft_memalloc(sizeof(t_ant));
		ants[i]->room = map->start;
		i++;
	}
	map->start->ant_nb = map->ant_pop;
	while (map->end->ant_nb != map->ant_pop)
	{
		ant = 0;
		while (ant < map->ant_pop)
		{
			i = path_len - 1;
			while (i >= 0 && ants[ant]->room->id != map->end->id)
			{
				if (ants[ant]->room->id == map->start->id)
				{
					next = get_room_from_id(map, path[0]);
					if (next->ant_nb == 0)
					{
						ft_printf("L%d-%s ", ant + 1, next->name);
						ants[ant]->room->ant_nb -= 1;
						ants[ant]->room = next;
						ants[ant]->room->ant_nb += 1;
						break ;
					}
				}
				else if (ants[ant]->room->id == path[i])
				{
					next = get_room_from_id(map, path[i + 1]);
					if (next->ant_nb == 0 || next->id == map->end->id)
					{
						ft_printf("L%d-%s ", ant + 1, next->name);
						ants[ant]->room->ant_nb -= 1;
						ants[ant]->room = next;
						ants[ant]->room->ant_nb += 1;
						break ;
					}
				}
				i--;
			}
			ant++;
		}
		ft_printf("\n");
	}
}

void	print_header(t_map *map)
{
	t_room	*room;
	t_room	*room2;
	int		i;
	int		j;

	ft_printf("%d\n", map->ant_pop);
	room = map->rooms;
	while (room)
	{
		if (room->id == map->start->id)
			ft_printf("##start\n");
		if (room->id == map->end->id)
			ft_printf("##end\n");
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
	}
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

int		main(int ac, char **av)
{
	t_list			*head;
	t_list			*next;
	t_map			*map;
	int				*path;
	int				path_len;

	(void)ac;
	(void)av;
	head = NULL;
	if (!(parse_file(&head)))
		return (ft_error("Error"));
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (ft_error("Error"));
	if (!(parse_map(map, head)))
		return (ft_error("Error"));
	if (!(path = (int *)malloc((map->room_nb + 1) * sizeof(int))))
		return (ft_error("Error"));
	ft_bzero(path, map->room_nb + 1);
	if (!(path_len = DFS(map, map->start, &path, 0)))
		return (ft_error("Error"));
	print_header(map);
	send_ants(map, path, path_len);
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
