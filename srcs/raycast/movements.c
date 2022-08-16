/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:20:03 by william           #+#    #+#             */
/*   Updated: 2022/08/16 19:49:44 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_right(t_game *game)
{
	double	old_vecdir_x;
	double	old_plane_x;

	old_vecdir_x = game->ray.vecdir_x;
	old_plane_x = game->planepos_x;
	game->ray.vecdir_x = game->ray.vecdir_x * cos(-ROTATE) - game->ray.vecdir_y
		* sin(-ROTATE);
	game->ray.vecdir_y = old_vecdir_x * sin(-ROTATE) + game->ray.vecdir_y
		* cos(-ROTATE);
	game->planepos_x = game->planepos_x * cos(-ROTATE) - game->planepos_y
		* sin(-ROTATE);
	game->planepos_y = old_plane_x * sin(-ROTATE) + game->planepos_y
		* cos(-ROTATE);
}

static void	do_rotation(t_game *game)
{
	double	old_vecdir_x;
	double	old_plane_x;

	old_vecdir_x = game->ray.vecdir_x;
	old_plane_x = game->planepos_x;
	if (game->move.left == TRUE)
	{
		game->ray.vecdir_x = game->ray.vecdir_x * cos(ROTATE)
			- game->ray.vecdir_y * sin(ROTATE);
		game->ray.vecdir_y = old_vecdir_x * sin(ROTATE)
			+ game->ray.vecdir_y + cos(ROTATE);
		game->planepos_x = game->planepos_x * cos(ROTATE)
			- game->planepos_y * sin(ROTATE);
		game->planepos_y = old_plane_x * sin(ROTATE)
			+ game->planepos_y * cos(ROTATE);
	}
	if (game->move.right == TRUE)
		rotate_right(game);
}

static void	do_line_movement(t_game *game)
{
	t_info	*info;

	info = game->infos;
	if (game->move.forward == TRUE)
	{
		if (info->i_map[(int)game->ray.init_pos_y]
			[(int)(game->ray.init_pos_x + game->ray.vecdir_x * SPEED)] == 0)
			game->ray.init_pos_x += game->ray.vecdir_x * SPEED;
		if (info->i_map[(int)(game->ray.init_pos_y
				+ game->ray.vecdir_y * SPEED)][(int)game->ray.init_pos_x] == 0)
			game->ray.init_pos_y += game->ray.vecdir_y * SPEED;
	}
	if (game->move.backward == TRUE)
	{
		if (info->i_map[(int)game->ray.init_pos_y]
			[(int)(game->ray.init_pos_x - game->ray.vecdir_x * SPEED)] == 0)
			game->ray.init_pos_x -= game->ray.vecdir_x * SPEED;
		if (info->i_map[(int)(game->ray.init_pos_y
				- game->ray.vecdir_y * SPEED)][(int)game->ray.init_pos_x] == 0)
			game->ray.init_pos_y -= game->ray.vecdir_y * SPEED;
	}
}

static void	do_side_movement(t_game *game)
{
	t_info	*info;

	info = game->infos;
	if (game->move.left == TRUE)
	{
		if (info->i_map[(int)game->ray.init_pos_y][(int)(game->ray.init_pos_x
			- game->ray.vecdir_y * SPEED)] == 0)
			game->ray.init_pos_x += game->ray.vecdir_y * SPEED;
		if (info->i_map[(int)(game->ray.init_pos_y + game->ray.vecdir_x
				* SPEED)][(int)game->ray.init_pos_x] == 0)
			game->ray.init_pos_y -= game->ray.vecdir_x * SPEED;
	}
	if (game->move.right == TRUE)
	{
		if (info->i_map[(int)game->ray.init_pos_y][(int)(game->ray.init_pos_x
			- game->ray.vecdir_y * SPEED)] == 0)
			game->ray.init_pos_x -= game->ray.vecdir_y * SPEED;
		if (info->i_map[(int)(game->ray.init_pos_y + game->ray.vecdir_x
				* SPEED)][(int)game->ray.init_pos_x] == 0)
			game->ray.init_pos_y += game->ray.vecdir_x * SPEED;
	}
}

void	check_for_moves(t_info *info)
{
	t_move	*move;

	move = &info->game.move;
	if (move->rot_right == TRUE || move->rot_left == TRUE)
		do_rotation(&info->game);
	if (move->forward == TRUE || move->backward == TRUE)
		do_line_movement(&info->game);
	if (move->left == TRUE || move->right == TRUE)
		do_side_movement(&info->game);
}