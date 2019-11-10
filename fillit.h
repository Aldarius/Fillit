/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:18:45 by lminta            #+#    #+#             */
/*   Updated: 2019/05/08 15:27:02 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>

typedef struct		s_tetr
{
	int				tetriminos[4][4];
	struct s_tetr	*next;
}					t_tetr;

typedef struct		s_minmax
{
	int				i_min;
	int				i_max;
	int				j_min;
	int				j_max;
}					t_minmax;

typedef struct		s_map
{
	int				**map;
	int				size;
}					t_map;

int					read_all(int fd, t_tetr **last);
t_tetr				*list_free(t_tetr *last);
int					re_map(int ***map, int size);
int					map_clean(int **map, int size);
t_map				*map_create(int size);
int					print_map(t_map *map);
int					fillit(t_map *map, t_tetr *last);
void				re_list(t_tetr **last);

#endif
