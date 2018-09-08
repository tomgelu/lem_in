/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:51:55 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 15:04:56 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_ant_population(t_map *map, t_list **lst)
{
	int			i;
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

t_ant		**alloc_and_init_ants(t_map *map)
{
	t_ant	**ants;
	int		i;

	i = 0;
	map->start->ant_nb = map->ant_pop;
	if (!(ants = (t_ant **)malloc(sizeof(t_ant *) * (map->ant_pop + 1))))
		return (NULL);
	while (i < map->ant_pop)
	{
		if (!(ants[i] = ft_memalloc(sizeof(t_ant))))
			return (NULL);
		ants[i]->room = map->start;
		ants[i]->id = i + 1;
		i++;
	}
	return (ants);
}
