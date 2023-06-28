/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:30:07 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/28 15:09:43 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_init(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	mlx_loop_hook(d->mlx->mlx, draw_frame, d);
	setup_hooks(d);
	mlx_loop(d->mlx->mlx);
	return (0);
}
