/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:05:48 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/08/09 23:14:09 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void get_textures(t_cub *cub, int tx)
{
	int x;
	int y;

    cub->tx_data[tx]->ptr = mlx_xpm_file_to_image(cub->mlx->mlx, cub->map->textures_paths[tx], &cub->tx_data[tx]->weight, &cub->tx_data[tx]->height);
    if(cub->tx_data[tx]->ptr == NULL)
        exit_cub(cub, 1); // corrigir
        
	cub->tx_data[tx]->data = (int *)mlx_get_data_addr(cub->tx_data[tx]->ptr, &cub->tx_data[tx]->bpp, &cub->tx_data[tx]->size_l, &cub->tx_data[tx]->endian);
    
	cub->tx_data[tx]->texture = (int **)malloc(sizeof(int *) * cub->tx_data[tx]->height);
        
	y = -1;
	while(++y < cub->tx_data[tx]->height)
    {
		cub->tx_data[tx]->texture[y] = (int *)malloc(sizeof(int) * cub->tx_data[tx]->weight);
   		x = -1;
		while(++x < cub->tx_data[tx]->weight)
			cub->tx_data[tx]->texture[y][x] = cub->tx_data[tx]->data[y * cub->tx_data[tx]->weight + x];
	}

    mlx_destroy_image(cub->mlx->mlx, cub->tx_data[tx]->ptr);
}

void init_textures(t_cub *cub)
{
    int i;

    i = -1;
    while(++i < 4)
    {
        cub->tx_data[i] = malloc(sizeof(t_texture));
        get_textures(cub, i);
    }
    // printf("NO:%i\n,SO:%i\n,WE:%i\n.EA:%i\n", cub->img[NO]->texture[35][35],cub->img[SO]->texture[35][35],cub->img[WE]->texture[35][35],cub->img[EA]->texture[35][35]);
}