/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:55:58 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 16:28:03 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_tab_length(char **tab)
{
	char	**cpy;
	int		i;

	cpy = tab;
	i = 0;
	while (*cpy++)
		i++;
	return (i);
}

t_room		*get_room_from_id(t_map *map, int id)
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

int			ft_is_sep(char *str, char c)
{
	int		i;

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
