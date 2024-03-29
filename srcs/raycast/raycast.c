/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:56:20 by wdebotte          #+#    #+#             */
/*   Updated: 2022/08/20 02:07:45 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	do_raycasting(t_game *game)
{
	int	x;

	x = -1;
	while (++x < game->infos->mlx.win_width)
	{
		ray_calculs(game, x);
		get_step_for_ray(game);
		get_next_hitten_wall(game);
		get_wall_and_draw_distance(game);
		draw_wall_line(game->infos, x);
	}
	mlx_put_image_to_window(game->infos->mlx.mlx, game->infos->mlx.window,
		game->infos->mlx.img.img, 0, 0);
	check_for_moves(game->infos);
	return (0);
}
