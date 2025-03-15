/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:01:14 by sellyani          #+#    #+#             */
/*   Updated: 2025/03/07 17:47:23 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static bool	around(char **map, int i, int j)
{
	if (ft_strchr("0C", map[i][j - 1]))
		map[i][j - 1] = 'M';
	else if (ft_strchr("0C", map[i][j + 1]))
		map[i][j + 1] = 'M';
	else if (ft_strchr("0C", map[i - 1][j]))
		map[i - 1][j] = 'M';
	else if (ft_strchr("0C", map[i + 1][j]))
		map[i + 1][j] = 'M';
	else
		return (false);
	return (true);
}

static bool	ft_test(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'C')
				return (false);
			else if (map[i][j] == 'E' && map[i - 1][j] != 'M' &&
				map[i + 1][j] != 'M' && map[i][j - 1] != 'M' &&
				map[i][j + 1] != 'M')
				return (false);
		}
	}
	return (true);
}

void	free_double(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

bool	handl_close(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P' && (map[i - 1][j] == 'E' ||
				map[i + 1][j] == 'E' || map[i][j - 1] == 'E' ||
				map[i][j + 1] =='E'))
				return (true);
			if (ft_strchr("MP", map[i][j]))
			{
				if (around(map, i, j))
				{
					i = -1;
					break ;
				}
			}
		}
	}
	return (ft_test(map));
}
