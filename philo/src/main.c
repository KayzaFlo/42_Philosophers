/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/08 16:30:59 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	wait_for_end(t_philo *philos, t_env *env)
{
	int	i;
	int	satiated_count;

	satiated_count = 0;
	while (satiated_count != env->count)
	{
		i = -1;
		satiated_count = 0;
		while (++i < env->count && !env->is_dead)
		{
			// pthread_mutex_lock(&env->meal);
			if ((int)(get_time() - philos[i].last_ate) >= env->time_to_die)
			{
				print_status("died", &philos[i], 1);
				env->is_dead = 1;
				return ;
			}
			if (env->max_eat_count && i < env->count)
				if (philos[i].ate_count >= env->max_eat_count)
					satiated_count++;
			// pthread_mutex_unlock(&env->meal);
		}
	}
	pthread_mutex_lock(&env->printing);
	printf("Each philosopher ate at least %d time(s).\n", env->max_eat_count);
	pthread_mutex_unlock(&env->printing);
	env->is_satiated = 1;
}

static int	parse_params(int argc, char *argv[], t_env *env)
{
	env->start_time = get_time();
	env->is_dead = 0;
	env->is_satiated = 0;

	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->max_eat_count = ft_atoi(argv[5]);
	else
		env->max_eat_count = 0;
	if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->max_eat_count < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!parse_params(argc, argv, &env))
		return (ft_return_error(ERR_PARAM));

	philos = malloc(env.count * sizeof(*philos));
	env.forks = malloc(env.count * sizeof(*env.forks));
	if (!philos || !(env.forks))
			return (ft_return_error("🔴 Error in Alloc!\n"));

	threads_init(philos, &env);
	wait_for_end(philos, &env);
	threads_exit(philos, &env);
	free(philos);
	free(env.forks);
	return (0);
}
