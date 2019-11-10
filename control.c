/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:51:09 by lminta            #+#    #+#             */
/*   Updated: 2019/05/08 15:28:06 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	print_error(int a)
{
	if (a == 0)
		ft_putstr("usage: ./fillit source_file\n");
	if (a == 1)
		ft_putstr("error\n");
	return (0);
}

void		re_list(t_tetr **last)
{
	t_tetr	*current;
	t_tetr	*buff;

	current = 0;
	buff = (*last)->next;
	while (buff)
	{
		buff = (*last)->next;
		(*last)->next = current;
		current = (*last);
		if (buff)
			(*last) = buff;
	}
}

int			main(int argc, char **argv)
{
	t_map	*map;
	t_tetr	*last;
	int		num;
	int		fd;

	if (argc != 2)
		return (print_error(0));
	fd = open(argv[1], O_RDONLY);
	if (!(num = read_all(fd, &last)))
		return (print_error(1));
	if (!(map = map_create(ft_sqrt(num * 4))))
		return ((int)list_free(last));
	while (!(fillit(map, last)))
		re_map(&(map->map), (map->size)++);
	list_free(last);
	map_clean(map->map, map->size);
	free(map);
	close(fd);
	return (0);
}
