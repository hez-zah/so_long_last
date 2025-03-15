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

#include "../so_long.h"

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
			else if (map[i][j] == 'E' && !ft_strchr("MP", map[i - 1][j]) &&
				!ft_strchr("MP", map[i + 1][j]) &&
				!ft_strchr("MP", map[i][j - 1]) &&
				!ft_strchr("MP", map[i][j + 1]))
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

void	free_image(t_map *slong)
{
	(void)slong;
	mlx_destroy_image(slong->mlx, slong->images.collect);
	mlx_destroy_image(slong->mlx, slong->images.space);
	mlx_destroy_image(slong->mlx, slong->images.wall);
	mlx_destroy_image(slong->mlx, slong->images.player_down);
	mlx_destroy_image(slong->mlx, slong->images.player_up);
	// mlx_destroy_image(slong->mlx, slong->images.exit_close);
	// mlx_destroy_image(slong->mlx, slong->images.exit_open);
	// free(slong->images.collect);
	// free(slong->images.space);
	// free(slong->images.wall);
	// free(slong->images.exit_close);
	free(slong->images.exit_open);
	// free(slong->images.player_down);
	// free(slong->images.player_up);
	// free(slong->images.player_left);
	// free(slong->images.player_right);
}
