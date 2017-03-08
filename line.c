/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 16:54:40 by mhalit            #+#    #+#             */
/*   Updated: 2017/02/19 16:54:46 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			mlx_pixel_image(t_fdf *env, int x, int y, int color)
{
	int			pos;

	pos = (x * (env->bpp / 8) + (y * env->size));
	env->data[pos] = color;
	env->data[pos + 1] = color >> 8;
	env->data[pos + 2] = color >> 16;
}

void			line(t_fdf *env)
{
	t_deriv		pts;

	pts.dx = abs(env->x1 - env->x0);
	pts.sx = env->x0 < env->x1 ? 1 : -1;
	pts.dy = abs(env->y1 - env->y0);
	pts.sy = env->y0 < env->y1 ? 1 : -1;
	pts.err = (pts.dx > pts.dy ? pts.dx : -pts.dy) / 2;
	while (42)
	{
		env->x0 < env->largeur && (env->x0 > 1) && env->y0 < env->hauteur &&
		(env->y0 > 1) ? mlx_pixel_image(env, env->x0, env->y0, env->color) : 0;
		if (env->x0 == env->x1 && env->y0 == env->y1)
			break ;
		pts.e2 = pts.err;
		if (pts.e2 > -pts.dx)
		{
			pts.err -= pts.dy;
			env->x0 += pts.sx;
		}
		if (pts.e2 < pts.dy)
		{
			pts.err += pts.dx;
			env->y0 += pts.sy;
		}
	}
}

int				display(int x, int y, t_fdf *env)
{
	if (x < env->xmax && y < env->ymax)
	{
		env->x0 = (x * env->zoom) * COS - (y * env->zoom) * SIN + env->basex;
		env->x1 = ((x + 1) * env->zoom) * COS - (y * env->zoom) * SIN +
		env->basex;
		env->y0 = (y * env->zoom) * COS + (x * env->zoom) * SIN / 2 +
		env->basey - (env->map[y][x] * env->zoom / 2);
		env->y1 = (y * env->zoom) * COS + (((x + 1) * env->zoom)) *
		SIN / 2 + env->basey - (env->map[y][x + 1] * env->zoom / 2);
		line(env);
		env->x0 = (x * env->zoom) * COS - (y * env->zoom) * SIN + env->basex;
		env->x1 = (x * env->zoom) * COS - ((y + 1) * env->zoom) *
		SIN + env->basex;
		env->y0 = (y * env->zoom) * COS + (x * env->zoom) * SIN / 2 +
		env->basey - (env->map[y][x] * env->zoom / 2);
		env->y1 = ((y + 1) * env->zoom) * COS + (x * env->zoom) * SIN / 2 +
		env->basey - (env->map[y + 1][x] * env->zoom / 2);
		line(env);
	}
	return (0);
}

int				launch(t_fdf *env)
{
	int			x;
	int			y;

	y = 0;
	env->image = mlx_new_image(env->init, env->largeur, env->hauteur);
	env->data = mlx_get_data_addr(env->image,
	&env->bpp, &env->size, &env->endian);
	while (y < env->ymax - 1)
	{
		x = 0;
		while (x < env->xmax)
		{
			if (env->map[y][x] == (env->zmax))
				env->color = 0x00FFFFF;
			else
				env->color = 0xFFFF00;
			display(x, y, env);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->init, env->win, env->image, 0, 0);
	ft_menu(env);
	return (0);
}

void			ft_menu(t_fdf *env)
{
	mlx_string_put(env->init, env->win, 50, 50, 0xFFFFFF, "--FdF Menu--");
	mlx_string_put(env->init, env->win, 50, 70, 0xFFFFFF, "----MOVE:---");
	mlx_string_put(env->init, env->win, 50, 90, 0xFFFFFF, "---UP DOWN--");
	mlx_string_put(env->init, env->win, 50, 110, 0xFFFFFF, "-LEFT RIGHT-");
	mlx_string_put(env->init, env->win, 50, 130, 0xFFFFFF, "------------");
	mlx_string_put(env->init, env->win, 50, 150, 0xFFFFFF, "----ZOOM:---");
	mlx_string_put(env->init, env->win, 50, 170, 0xFFFFFF, "--  + -   --");
	mlx_string_put(env->init, env->win, 50, 190, 0xFFFFFF, "----ANGLE:--");
	mlx_string_put(env->init, env->win, 50, 210, 0xFFFFFF, "--  =  /  --");
	mlx_string_put(env->init, env->win, 50, 230, 0xFFFFFF, "------------");
}
