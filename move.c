/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:11:16 by lminta            #+#    #+#             */
/*   Updated: 2019/05/07 14:53:18 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_minmax	min_max(t_tetr *last)
{
	t_minmax	j_i;
	t_minmax	i_j;

	j_i.i_max = 0;
	j_i.i_min = 4;
	j_i.j_max = 0;
	j_i.j_min = 4;
	i_j.i_max = 0;
	while (i_j.i_max < 4)
	{
		i_j.j_max = 0;
		while (i_j.j_max < 4)
		{
			if (last->tetriminos[i_j.i_max][i_j.j_max])
			{
				(i_j.i_max < j_i.i_min) ? j_i.i_min = i_j.i_max : j_i.i_min;
				(i_j.j_max < j_i.j_min) ? j_i.j_min = i_j.j_max : j_i.j_min;
				(i_j.i_max > j_i.i_max) ? j_i.i_max = i_j.i_max : j_i.i_max;
				(i_j.j_max > j_i.j_max) ? j_i.j_max = i_j.j_max : j_i.j_max;
			}
			i_j.j_max++;
		}
		i_j.i_max++;
	}
	return (j_i);
}

static void		dl_tetr(t_map *map, t_tetr *last, int i_s, int j_s)
{
	t_minmax	mm;
	int			i;
	int			j;

	mm = min_max(last);
	i = 0;
	while (mm.i_min + i <= mm.i_max)
	{
		j = 0;
		while (mm.j_min + j <= mm.j_max)
		{
			if (last->tetriminos[mm.i_min + i][mm.j_min + j] != 0)
				map->map[i_s + i][j_s + j] = 0;
			j++;
		}
		i++;
	}
}

static int		test_pl_tetr(t_map *map, t_tetr *last, int i_s, int j_s)
{
	t_minmax	mm;
	int			i;
	int			j;

	mm = min_max(last);
	i = 0;
	while (mm.i_min + i <= mm.i_max)
	{
		j = 0;
		while (mm.j_min + j <= mm.j_max)
		{
			if (last->tetriminos[mm.i_min + i][mm.j_min + j] != 0 &&
			(i_s + i >= map->size || j_s + j >= map->size ||
			map->map[i_s + i][j_s + j] != 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int		pl_tetr(t_map *map, t_tetr *last, int i_s, int j_s)
{
	t_minmax	mm;
	int			i;
	int			j;

	mm = min_max(last);
	if (!(test_pl_tetr(map, last, i_s, j_s)))
		return (0);
	i = 0;
	while (mm.i_min + i <= mm.i_max)
	{
		j = 0;
		while (mm.j_min + j <= mm.j_max)
		{
			if (last->tetriminos[mm.i_min + i][mm.j_min + j] != 0)
				map->map[i_s + i][j_s + j] =
				last->tetriminos[mm.i_min + i][mm.j_min + j];
			j++;
		}
		i++;
	}
	return (1);
}

int				fillit(t_map *map, t_tetr *last)
{
	int i;
	int j;

	i = 0;
	if (!last)
		return (print_map(map));
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			if (pl_tetr(map, last, i, j))
			{
				if (fillit(map, last->next))
					return (1);
				else
					dl_tetr(map, last, i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}
