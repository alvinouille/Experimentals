/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:51:50 by alvina            #+#    #+#             */
/*   Updated: 2023/05/11 17:43:24 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void    init_texture(t_game *game)
{
    game->texture[0].img.img = mlx_xpm_file_to_image(game->mlx, "img/visage.xpm", &(game->texture[0].width), &(game->texture[0].height));
    game->texture[0].tab = (int *)mlx_get_data_addr(game->texture[0].img.img, &game->texture[0].img.bits_per_pixel,
                                                &game->texture[0].img.line_length, &game->texture[0].img.endian);
    game->texture[1].img.img = mlx_xpm_file_to_image(game->mlx, "img/visagee.xpm", &(game->texture[1].width), &(game->texture[1].height));
    game->texture[1].tab = (int *)mlx_get_data_addr(game->texture[1].img.img, &game->texture[1].img.bits_per_pixel,
                                                &game->texture[1].img.line_length, &game->texture[1].img.endian);
    game->texture[2].img.img = mlx_xpm_file_to_image(game->mlx, "img/bojii.xpm", &(game->texture[2].width), &(game->texture[2].height));
    game->texture[2].tab = (int *)mlx_get_data_addr(game->texture[2].img.img, &game->texture[2].img.bits_per_pixel,
                                                &game->texture[0].img.line_length, &game->texture[0].img.endian);
    game->texture[3].img.img = mlx_xpm_file_to_image(game->mlx, "img/naru.xpm", &(game->texture[3].width), &(game->texture[3].height));
    game->texture[3].tab = (int *)mlx_get_data_addr(game->texture[3].img.img, &game->texture[3].img.bits_per_pixel,
                                                &game->texture[3].img.line_length, &game->texture[3].img.endian);
}