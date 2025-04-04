/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evente.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sellyani <sellyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:56:32 by sellyani          #+#    #+#             */
/*   Updated: 2025/03/07 17:55:29 by sellyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	demi_move_aid(t_map *slong, int i, int j)
{
	if (i == 1 && !j)
		mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_down,
			slong->y_p * SIZE, slong->x_p * SIZE);
	else if (i == -1 && !j)
		mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_up,
			slong->y_p * SIZE, slong->x_p * SIZE);
	else if (!i && j == 1)
		mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_right,
			slong->y_p * SIZE, slong->x_p * SIZE);
	else if (!i && j == -1)
		mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_left,
			slong->y_p * SIZE, slong->x_p * SIZE);
}

void	demi_move(t_map *slong, int i, int j, bool sign)
{
	if (sign)
	{
		if (i == 1 && !j)
			mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_down,
				(slong->y_p + j) * SIZE, (slong->x_p + i) * SIZE);
		else if (i == -1 && !j)
			mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_up,
				(slong->y_p + j) * SIZE, (slong->x_p + i) * SIZE);
		else if (!i && j == 1)
			mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_right,
				(slong->y_p + j) * SIZE, (slong->x_p + i) * SIZE);
		else if (!i && j == -1)
			mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.player_left,
				(slong->y_p + j) * SIZE, (slong->x_p + i) * SIZE);
	}
	else
		demi_move_aid(slong, i, j);
}

void	put_move(t_map *slong, int i, int j)
{
	char	*dmp;

	// mlx_destroy_image(slong->mlx, slong->mlx_img);
	// slong->mlx_img = mlx_xpm_file_to_image(slong->mlx,
	// 		SPACE, &slong->h_map, &slong->w_map);
	mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.space,
		(slong->y_p) * SIZE, (slong->x_p) * SIZE);
	// mlx_destroy_image(slong->mlx, slong->mlx_img);
	demi_move(slong, i, j, true);
	slong->x_p += i;
	slong->y_p += j;
	// mlx_destroy_image(slong->mlx, slong->mlx_img);
	// slong->mlx_img = mlx_xpm_file_to_image(slong->mlx,
	// 		WALL, &slong->h_map, &slong->w_map);
	dmp = ft_itoa(slong->move);
	mlx_put_image_to_window(slong->mlx, slong->mlx_win, slong->images.wall, SIZE, 0);
	mlx_string_put(slong->mlx, slong->mlx_win, 60, 15, 0x00ffff, dmp);
	free(dmp);
}

void	ft_go(t_map **slong, int i, int j)
{
	if ((*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] == '1' ||
		((*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] == 'E' &&
		(*slong)->collect))
		return (demi_move(*slong, i, j, false));
	if ((*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] == 'C' ||
		(*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] == '0')
	{
		if ((*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] == 'C')
			(*slong)->collect -= 1;
		(*slong)->map[(*slong)->x_p][(*slong)->y_p] = '0';
		(*slong)->map[(*slong)->x_p + i][(*slong)->y_p + j] = 'P';
		(*slong)->move += 1;
	}
	ft_go_aid(slong, i, j);
	if (!(*slong)->collect)
		ft_ft(*slong);
	put_move(*slong, i, j);
}

int	ft_hook(int prees, t_map **slong)
{
	if (prees == 1)
		ft_go(slong, 1, 0);
	else if (prees == 13)
		ft_go(slong, -1, 0);
	else if (prees == 2)
		ft_go(slong, 0, 1);
	else if (prees == 0)
		ft_go(slong, 0, -1);
	else if (prees == 53)
	{
		ft_putendl_fd("Exit :(", 1);
		free_double((*slong)->map);
		mlx_destroy_window((*slong)->mlx, (*slong)->mlx_win);
		exit(1);
	}
	return (1);
}
