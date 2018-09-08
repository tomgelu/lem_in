/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:53:56 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 15:05:20 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_coords_available(t_map *map, int x, int y)
{
	t_room	*current;

	current = map->rooms;
	while (current)
	{
		if (current->id != map->room_nb)
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

char		*get_room_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;
	return (ft_strsub(str, 0, i));
}

int			get_room_coords(char *str, int coord)
{
	int		i;
	int		j;
	int		offset;

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
