/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:21:24 by lminta            #+#    #+#             */
/*   Updated: 2019/05/10 13:32:16 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		check_nei(t_tetr *tet, int i, int j)
{
	int sum;

	sum = 0;
	if (i != 3)
		(tet->tetriminos[i + 1][j] != 0) ? sum++ : sum;
	if (i != 0)
		(tet->tetriminos[i - 1][j] != 0) ? sum++ : sum;
	if (j != 3)
		(tet->tetriminos[i][j + 1] != 0) ? sum++ : sum;
	if (j != 0)
		(tet->tetriminos[i][j - 1] != 0) ? sum++ : sum;
	return (sum);
}

static int		test_tetrimino(t_tetr *tetra)
{
	int	tetra_size;
	int	tetra_q;
	int	i;
	int	j;

	tetra_size = 0;
	tetra_q = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (tetra->tetriminos[i][j] != 0)
			{
				tetra_size++;
				tetra_q += check_nei(tetra, i, j);
			}
			j++;
		}
		i++;
	}
	if (tetra_size != 4 || tetra_q < 6)
		return (0);
	return (1);
}

static t_tetr	*reader(char *buff, char c)
{
	t_tetr	*tetra;
	int		i;

	if (!(tetra = (t_tetr *)malloc(sizeof(t_tetr))))
		return (0);
	buff[21] = '\0';
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '#' && (i + 1) % 5 != 0 && i < 19)
			tetra->tetriminos[i / 5][i % 5] = (int)c;
		else if (buff[i] == '.' && (i + 1) % 5 != 0 && i < 19)
			tetra->tetriminos[i / 5][i % 5] = 0;
		else if (buff[i] == '\n' && ((i + 1) % 5 == 0 || i == 20))
			(void)0;
		else
			return (list_free(tetra));
		i++;
	}
	if (!(test_tetrimino(tetra)) || c > 'Z')
		return (list_free(tetra));
	return (tetra);
}

t_tetr			*list_free(t_tetr *last)
{
	if (last)
	{
		if (last->next)
			list_free(last->next);
		free(last);
	}
	return (0);
}

int				read_all(int fd, t_tetr **last)
{
	t_tetr	*tetra;
	int		err;
	int		flag;
	char	c;
	char	buff[22];

	if (fd < 0)
		return (0);
	*last = 0;
	c = 'A';
	while ((err = read(fd, buff, 21)) > 19)
	{
		buff[err - 1] = '\0';
		if (!(tetra = reader(buff, c)))
			return ((int)list_free(*last));
		tetra->next = *last;
		*last = tetra;
		c++;
		flag = err;
	}
	if (flag != 20)
		return ((int)list_free(*last));
	if (c > 'A')
		re_list(last);
	return ((int)(c - 'A'));
}
