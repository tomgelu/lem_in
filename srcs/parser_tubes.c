/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tubes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:47:53 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 19:00:05 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_tubes(t_map *map, t_list *current)
{
	char	*str;

	while (current)
	{
		str = current->content;
		if (count_digits(str, "-") == 2)
			if (!(handle_tube(map, str)))
				return (-1);
		current = current->next;
	}
	return (1);
}

int			handle_tube(t_map *map, char *str)
{
	int		i;
	int		j;
	char	*room1;
	char	*room2;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '-')
		i++;
	room1 = ft_strsub(str, 0, i);
	i++;
	while (str[i + j])
		j++;
	room2 = ft_strsub(str, i, j);
	if (room_exists(map, room1) && room_exists(map, room2))
		connect_rooms(map, room_exists(map, room1), room_exists(map, room2));
	else
	{
		ft_strdel(&room1);
		ft_strdel(&room2);
		return (0);
	}
	ft_strdel(&room1);
	ft_strdel(&room2);
	return (1);
}
