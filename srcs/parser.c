/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:48:04 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/05 15:06:22 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_file(t_list **head)
{
	char			*tmp;

	while (get_next_line(0, &tmp) > 0)
	{
		if (!ft_isprint(tmp[0]))
			return (0);
		if (!(*head))
			*head = ft_lstnew(tmp,
					(ft_strlen(tmp) + 1) * sizeof(char));
		else
			ft_lstappend(*head, tmp,
					(ft_strlen(tmp) + 1) * sizeof(char));
		ft_strdel(&tmp);
	}
	if (!(*head))
		return (0);
	return (1);
}

int			parse_ant_population(t_map *map, t_list **lst)
{
	int 		i;
	char		*tmp;

	i = 0;
	while ((*lst)->content && ((char *)(*lst)->content)[0] == '#')
		*lst = (*lst)->next;
	if (!((*lst)->content))
	{
		map->ant_pop = -1;
		return (0);
	}
	tmp = (char *)(*lst)->content;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			map->ant_pop = -1;
			return (0);
		}
		i++;
	}
	map->ant_pop = ft_atoi(tmp);
	if (map->ant_pop <= 0)
		return (0);
	return (1);
}

int			get_tab_length(char **tab)
{
	char		**cpy;
	int			i;

	cpy = tab;
	i = 0;
	while (*cpy++)
		i++;
	return (i);
}

int			handle_hashtag(t_map *map, char* str, int *modifier)
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

int			is_coords_available(t_map* map, int x, int y, int id)
{
	t_room	*current;

	current = map->rooms;
	while (current)
	{
		if (current->id != id)
		{
			if (x == current->x && y == current->y)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

t_room		*room_exists(t_map *map, char *name)
{
	t_room	*current;

	current = map->rooms;
	while (current)
	{
		if (strcmp(name, current->name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int			connect_rooms(t_map *map, t_room *room1, t_room *room2)
{
	map->connections[room1->id][room2->id] = 1;
	map->connections[room2->id][room1->id] = 1;
	return (1);
}

int		handle_tube(t_map *map, char *str)
{
	int		i;
	int		j;
	char	*room1;
	char	*room2;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '-')
		i++;
	room1 = ft_strsub(str, 0, i);
	i++;
	while (str[i + j])
		j++;	
	room2 = ft_strsub(str, i, j);
	if (room_exists(map, room1) && room_exists(map, room2))
		connect_rooms(map, room_exists(map, room1), room_exists(map, room2));
	else
		return (0);
	return (1);
}

char		*get_room_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;
	return(ft_strsub(str, 0, i));
}

int         get_room_coords(char *str, int coord)
{
	int     i;
	int		j;
	int     offset;

	i = 0;
	offset = 0;
	while (str[i] && offset != coord)
	{
		while (str[i] != ' ')
			i++;
		i++;
		offset++;
	}
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
	{
		if (!ft_isdigit(str[i + j]))
			return (-1);
		j++;
	}
	return (ft_atoi(str + i));
}

int			handle_room(t_map *map, char *str, int *modifier, int *room_nb)
{
	t_room	*new;

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
	map->last->next = NULL;
	map->last->name = get_room_name(str);
	map->last->id = *room_nb;
	map->last->ant_nb = 0;
	if ((map->last->x = get_room_coords(str, 1)) == -1)
		return (0);
	if ((map->last->y = get_room_coords(str, 2)) == -1)
		return (0);
	if (!(is_coords_available(map, map->last->x, map->last->y, *room_nb)))
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
	(*room_nb)++;
	return (1);
}

int		ft_is_sep(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			count_digits(char *str, char *sep)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && !ft_is_sep(sep, str[i]))
		{
			i++;
			if (!str[i] || ft_is_sep(sep, str[i]))
				words += 1;
		}
		if (str[i])
			i++;
	}
	return (words);
}

int			parse_map(t_map *map, t_list *head)
{
	t_list		*current;
	int			i;
	int			modifier;
	char		*str;
	int			room_nb;

	room_nb = 0;
	current = head;
	if (!(parse_ant_population(map, &current)))
		return (0);
	current = current->next;
	while (current && count_digits((char *)current->content, "-") != 2)
	{
		str = current->content;
		if (str && str[0] == '#')
		{
			if (!(handle_hashtag(map, current->content, &modifier)))
				return (0);
		}
		else if (count_digits(current->content, " ") == 3)
		{
			if (!(handle_room(map, current->content, &modifier, &room_nb)))
				return (0);
		}
		else
			return (0);
		current = current->next;
	}
	if (!(map->connections = (int **)malloc(sizeof(int *) * (room_nb + 1))))
		return (0);
	i = -1;
	while (++i < room_nb)
		map->connections[i] = (int *)malloc(sizeof(int) * (room_nb + 1));
	
	while (current)
	{
		str = current->content;
		if (count_digits(str, "-") == 2)
			if (!(handle_tube(map, str)))
				return (0);
		current = current->next;
	}
	map->room_nb = room_nb;
	if (!map->start || !map->end)
		return (0);
	return (1);
}
