/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 16:07:52 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	isnum(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	parse_params(int argc, char *argv[], t_env *env)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!isnum(argv[i]))
			return (0);
	env->start_time = get_time();
	env->is_dead = 0;
	env->is_satiated = 0;
	env->count = atoi_overflow(argv[1]);
	env->time_to_die = atoi_overflow(argv[2]);
	env->time_to_eat = atoi_overflow(argv[3]);
	env->time_to_sleep = atoi_overflow(argv[4]);
	if (argc == 6)
		env->max_eat_count = atoi_overflow(argv[5]);
	else
		env->max_eat_count = 0;
	if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->max_eat_count < 0)
		return (0);
	return (1);
}
