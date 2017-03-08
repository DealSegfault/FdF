/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 20:04:32 by mhalit            #+#    #+#             */
/*   Updated: 2017/02/19 16:58:44 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				k_hook(int keycode, t_fdf *env)
{
	if (keycode == ESC)
		exit(42);
	if (keycode == LEFT || keycode == RIGHT || keycode == UP || keycode == DOWN)
	{
		mlx_destroy_image(env->init, env->image);
		if (keycode <= 124)
			keycode == LEFT ? env->basex -= 10 : (env->basex += 10);
		else
			keycode == UP ? env->basey -= 10 : (env->basey += 10);
		launch(env);
	}
	if (keycode == PLUS || keycode == MINUS)
	{
		mlx_destroy_image(env->init, env->image);
		keycode == PLUS ? env->zoom += 5 : (env->zoom -= 5);
		launch(env);
	}
	if (keycode == AP || keycode == AM)
	{
		mlx_destroy_image(env->init, env->image);
		keycode == AP ? env->angle += 10 : (env->angle -= 10);
		launch(env);
	}
	return (0);
}

int				*sp_toi(char **line, t_fdf **info)
{
	int			*out;
	int			y;

	y = 0;
	while (line[y])
		y++;
	if ((*info)->xmax && y < (*info)->xmax)
	{
		return (NULL);
	}
	(*info)->xmax = y;
	if (!(out = (int *)malloc(sizeof(int) * (y + 1))))
		return (NULL);
	y = 0;
	while (line[y])
	{
		ft_atoi(line[y]) > (*info)->zmax ? (*info)->zmax = ft_atoi(line[y]) : 0;
		ft_atoi(line[y]) < (*info)->zmin ? (*info)->zmin = ft_atoi(line[y]) : 0;
		*out++ = ft_atoi(line[y]);
		y++;
	}
	*out = '\0';
	out = out - y;
	return (out);
}

void			init(t_fdf **env)
{
	(*env)->zoom = 5;
	(*env)->angle = 20;
	(*env)->color = 0x00FFFFF;
	(*env)->init = mlx_init();
	(*env)->largeur = 2300;
	(*env)->hauteur = 1300;
	(*env)->win = mlx_new_window((*env)->init,
	(*env)->largeur, (*env)->hauteur, "Title");
	(*env)->basex = 1;
	(*env)->basey = 1;
	while ((*env)->xmax * (*env)->ymax * (*env)->zoom <=
	((*env)->largeur * (*env)->hauteur) / (*env)->zoom / 4)
		(*env)->zoom = (*env)->zoom + 1;
	(*env)->basex = ((*env)->largeur - ((*env)->xmax * (*env)->zoom));
	(*env)->basey = ((*env)->hauteur - ((*env)->ymax * (*env)->zoom)) / 2;
}

int				count(t_fdf **env, char *file)
{
	int			i;
	int			c;
	int			rd;
	int			fd;
	char		buffer[BUFF_SIZE + 1];

	i = 0;
	rd = 0;
	fd = open(file, O_RDONLY);
	while ((rd = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[rd] = '\0';
		c = 0;
		while (buffer[c])
		{
			if (buffer[c] == '\n')
				i++;
			c++;
		}
	}
	(*env)->ymax = i;
	if (!((*env)->map = (int **)malloc(sizeof(int *) * i + 1)))
		return (0);
	return (i);
}

int				main(int argc, char *argv[])
{
	int			fd;
	char		*line;
	t_fdf		*env;

	if (!(env = (t_fdf *)malloc(sizeof(t_fdf))))
		return (0);
	if (argc == 2)
	{
		count(&env, argv[1]);
		env->zmax = 0;
		env->zmin = 0;
		fd = open(argv[1], O_RDONLY);
		while ((get_next_line(fd, &line)) > 0)
		{
			if (!(*(env->map)++ = sp_toi(ft_strsplit(line, ' '), &env)))
				break ;
		}
		env->map = env->map - env->ymax;
		init(&env);
		launch(env);
		mlx_key_hook(env->win, k_hook, env);
		mlx_loop(env->init);
	}
	else
		ft_putstr("Usage : ./fdf <filename> [case_size z_size ]\n");
}
