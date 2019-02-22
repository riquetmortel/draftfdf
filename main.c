/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/22 18:10:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_it(int fd)
{
	char *final = NULL;
	char stock[BUFF_SIZE + 1];
	int i;

	while ((i = read(fd, stock, BUFF_SIZE)) > 0)
    {
        stock[i] = '\0';
        final = ft_strjoin2(final, stock);
    }
	return (final);
}

void ligne(t_fdf *env, int pt, int color) {
	int *pixels = (int *)env->info;
	int x0;  
	int y0;
	int y1;
	int x1;
	int i;
	int xinc, yinc;
	int cumul;

		x0 = env->zoom * env->coord[pt][0];
		y0 = env->zoom * env->coord[pt][1];
		x1 = env->zoom * env->coord[pt + 1][0];
		y1 = env->zoom * env->coord[pt + 1][1];
		
	//	printf (" FROM PT %d : %d, %d -> TO PT %d, %d, %d\n", pt, x0, y0, (pt+1), x1, y1);
		int dx = x1 - x0;
		int dy = y1 - y0;
		xinc = ( dx > 0 ) ? 1 : -1 ;
 		yinc = ( dy > 0 ) ? 1 : -1 ;

	//	printf ("PT %d DX %d DY %d yo\n", pt, dx, dy);
		pixels[(y0 * 2560 + x0)] = color;
		if ( dx > dy ) 
		{
			
    		cumul = dx / 2 ;
   			 for ( i = 1 ; i <= dx ; i++ ) 
			{
      			x0 += xinc ;
      			cumul += dy ;
      			if ( cumul >= dx ) 
				{
        			cumul -= dx ;
        			y0 += yinc ; 
				}
		//		printf ("color %d \n", (y0 * env->x_width + x0));
      			pixels[(y0 * 2560 + x0)] = color; 
	  		} 
	  }
    else 
	{
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) 
	{
    	  y0 += yinc ;
      	cumul += dx ;
     	 if ( cumul >= dy ) {
     	   cumul -= dy ;
     	   x0 += xinc ; }
     		//pixels[(y0 * env->x_width + x0)] = color;
		 // printf ("coloring %d\n", (y0 * env->x_width* env->zoom + x0));
	  }
	}
}
	 
void colonne(t_fdf *env, int pt, int color) 
{
	int *pixels = (int *)env->info;
	int x0;  
	int y0;
	int y1;
	int x1;
	int i;
	int xinc, yinc;
	int cumul;
	//int w = 0;

	x0 = env->zoom * env->coord[pt][0];
	y0 = env->zoom * env->coord[pt][1];
	x1 = env->zoom * env->coord[pt + env->x_width][0];
	y1 = env->zoom * env->coord[pt + env->x_width][1];
//	printf ("ENV ZOOM %d\n", env->zoom);
		
	//printf (" FROM PT %d : %d, %d -> TO PT %d, %d, %d\n", pt, x0, y0, (pt+1), x1, y1);
	int dx = x1 - x0;
	int dy = y1 - y0;
	xinc = ( dx > 0 ) ? 1 : -1 ;
 	yinc = ( dy > 0 ) ? 1 : -1 ;

//	printf ("PT %d DX %d DY %d yo\n", pt, dx, dy);
		pixels[(y0 * 2560 + x0)] = color;
		//printf ("WESH\n");
		if ( dx > dy ) 
		{
			
    		cumul = dx / 2 ;
   			 for ( i = 1 ; i <= dx ; i++ ) 
			{
      			x0 += xinc ;
      			cumul += dy ;
      			if ( cumul >= dx ) 
				{
        			cumul -= dx ;
        			y0 += yinc ; 
				}
			//	printf ("color %d \n", (y0 * env->x_width + x0));
      			pixels[(y0 * 2560 + x0)] = color; 
	  		} 
	  }
    else 
	{
    	cumul = dy / 2 ;
 		for ( i = 1 ; i <= dy ; i++ ) 
		{
    		y0 += yinc ;
     		cumul += dx ;
     	 if ( cumul >= dy ) 
		  {
     	  	 cumul -= dy ;
     	  	 x0 += xinc ; 
		}
		if (env->coord[pt][2] != 0)
			pixels[(y0 * 2560 + x0)] = 0xff6666;
		else
     		pixels[(y0 * 2560 + x0)] = color;
		//  printf ("coloring %d\n", (y0 * env->x_width * env->zoom + x0));
	  }
	}
}

void sendpoints(t_fdf *env)
{
	int pt = 0;
	while (pt < env->size - 1)
	{
		ligne(env, pt, 0xFFFFFF);
		pt++;
	}
	pt = 0;
	while (pt < env->size - env->x_width)
	{
		colonne(env, pt, 0xFFFFFF);
		pt++;
	}
}

int		main(int ac,char **argv)
{
	int fd;
	t_fdf env;
	char *file = NULL;
	int endian;
	int bpp;
    int size_line;
	//int i = 0;

	if (ac != 2)
		return (-1); //a gerer later les exceptions et tutti quanti babe 
	fd = open(argv[1], O_RDONLY);
	ft_analyse(&file, fd, &env);
	//printf("OK\n");

	printf("env X %d Y %d SIZE %d...\n", env.x_width, env.y_height, env.size);
//	while (i++ < 208)
//		printf("DATA COORD %f %f %f\n", env.coord[i][0], env.coord[i][1], env.coord[i][2]);

    env.mlx_ptr = mlx_init();
  	env.win_ptr = mlx_new_window(env.mlx_ptr, 2560, 2560, "fdf");
	env.img_ptr = mlx_new_image(env.mlx_ptr, 2560, 2560);
    env.info = mlx_get_data_addr(env.img_ptr, &(bpp), &(size_line), &(endian));
	env.zoom = 30;
	// printf("ENV %s\n", env.info);
	sendpoints(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 1000, 500);
	mlx_key_hook(env.win_ptr, closewin, &env);
	mlx_key_hook(env.win_ptr, zoom, &env);
    // printf("INFO = %s\n", env.info);
    mlx_loop(env.mlx_ptr);
    return(0);
}
	