/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:48:04 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 20:34:19 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_file(t_list **head)
{
	char			*tmp;

	while (get_next_line(0, &tmp) > 0)
	{
		if (!tmp || (!ft_isprint(tmp[0])
				&& !(tmp[0] == '\0' || tmp[0] == '\n')))
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

int			parse_line(t_map *map, char *str, int *modifier)
{
	if (str && str[0] == '#')
	{
		if (!(handle_hashtag(map, str, modifier)))
			return (0);
	}
	else if (count_digits(str, " ") == 3)
	{
		if (!(handle_room(map, str, modifier)))
			return (0);
	}
	else
		return (0);
	return (1);
}

int			parse_map(t_map *map, t_list *head)
{
	t_list		*current;
	int			i;
	int			modifier;

	map->room_nb = 0;
	current = head;
	if (!(parse_ant_population(map, &current)))
		return (0);
	current = current->next;
	while (current && count_digits((char *)current->content, "-") != 2)
	{
		if (!(parse_line(map, current->content, &modifier)))
			return (0);
		current = current->next;
	}
	if (!(map->connections = (int**)malloc(sizeof(int*) * (map->room_nb + 1))))
		return (0);
	i = -1;
	while (++i < map->room_nb)
		if (!(map->connections[i] = (int*)ft_memalloc(sizeof(int)
			* (map->room_nb + 1))))
			return (0);
	if (!map->start || !map->end || !(parse_tubes(map, current)))
		return (0);
	return (1);
}
