/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:50:13 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 16:32:26 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "get_next_line.h"
# include "../lib/inc/ft_printf.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				id;
	int				visited;
	struct s_room	*next;
	int				ant_nb;
}					t_room;

typedef struct		s_map
{
	int				ant_pop;
	struct s_room	*start;
	struct s_room	*end;
	struct s_room	*rooms;
	struct s_room	*last;
	int				room_nb;
	int				**connections;
}					t_map;

typedef struct		s_ant
{
	struct s_room	*room;
	int				id;
}					t_ant;

int					get_tab_length(char **tab);
int					parse_file(t_list **head);
int					parse_map(t_map *map, t_list *head);
int					dfs(t_map *map, t_room *room, int **path, int depth);
t_room				*get_room_from_id(t_map *map, int id);
void				print_header(t_map *map);
void				send_ants(t_map *map, int *path, int path_len);
t_ant				**alloc_and_init_ants(t_map *map);
int					parse_ant_population(t_map *map, t_list **lst);
int					count_digits(char *str, char *sep);
int					handle_hashtag(t_map *map, char *str, int *modifier);
int					handle_room(t_map *map, char *str, int *modifier);
int					parse_tubes(t_map *map, t_list *current);
t_room				*room_exists(t_map *map, char *name);
char				*get_room_name(char *str);
int					get_room_coords(char *str, int coord);
int					is_coords_available(t_map *map, int x, int y);
int					handle_tube(t_map *map, char *str);
int					connect_rooms(t_map *map, t_room *room1, t_room *room2);
int					free_lines(t_list *head);
int					ft_error(char *error);
int					free_hole(t_list *head, t_map *map, int *path);
int					free_map(t_map *map);
int					free_path(int *path);
void				free_ants(t_ant **, int ant_nb);

#endif
