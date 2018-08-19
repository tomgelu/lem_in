/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:50:13 by tgelu             #+#    #+#             */
/*   Updated: 2018/08/19 22:12:04 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
#define LEM_IN
#include "get_next_line.h"
#include "../lib/inc/ft_printf.h"

typedef struct				s_room
{
	char					*name;
	int						x;
	int						y;
	int						id;
	int						visited;
	struct s_room			*next;
}							t_room;

typedef struct				s_map
{
	int						ant_pop;	
	struct s_room			*start;
	struct s_room			*end;
	struct s_room			*rooms;
	int						room_nb;
	struct s_room			*last;
	int						**connections;
}							t_map;

typedef struct				s_ant
{
	struct s_room			*room;
}							t_ant;

int				parse_file(t_list **head);
int				parse_map(t_map *map, t_list *head);

#endif
