/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:05:06 by mhalit            #+#    #+#             */
/*   Updated: 2017/02/19 16:54:29 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define AP 81
# define AM 75
# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define PLUS 69
# define MINUS 78
# define COS cos(M_PI * env->angle / 180)
# define SIN sin(M_PI * env->angle / 180)

typedef struct		s_fdf
{
	int				**map;
	void			*init;
	void			*win;
	void			*image;
	double			angle;
	int				zmax;
	int				zmin;
	int				xmax;
	int				ymax;
	int				zoom;
	int				basex;
	int				basey;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				color;
	int				largeur;
	int				hauteur;
	int				bpp;
	int				size;
	int				endian;
	char			*data;
}					t_fdf;

typedef struct		s_deriv
{
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
}					t_deriv;

void				mlx_pixel_image(t_fdf *env, int x, int y, int color);
void				line(t_fdf *env);
int					display(int x, int y, t_fdf *env);
int					launch(t_fdf *env);
int					k_hook(int keycode, t_fdf *env);
int					*sp_toi(char **line, t_fdf **info);
void				init(t_fdf **env);
int					count(t_fdf **env, char *file);
int					main(int argc, char *argv[]);
void				ft_menu(t_fdf *env);
#endif
