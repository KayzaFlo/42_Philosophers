/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/07 16:45:08 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	wait_for_end(t_philo *philos, t_env *env)
{
	int	i;
	// int	max_ate;

	// max_ate = 0;
	while (!env->do_stop)
	{
		i = -1;
		while (++i < env->count && !env->do_stop)
		{
			// pthread_mutex_lock(&env->meal);
			if ((int)(get_time() - philos[i].last_ate) >= env->time_to_die)
			{
				philo_print("died", &philos[i], 1);
				env->do_stop = 1;
			return ;
			}
			// pthread_mutex_unlock(&env->meal);
		}
		// if (env->do_stop)
			// break ;
		i = 0;
			// printf("%d %d %d \n", env->count, philos[i].ate_count, env->max_ate);
		while (env->max_eat_count && i < env->count
			&& philos[i].ate_count >= env->max_eat_count)
			i++;
		env->do_stop = (i == env->count);
	}
		printf("All philos ate min %d times.\n", env->max_eat_count);
}

static int	parse_params(int argc, char *argv[], t_env *env)
{
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

	// env.start_time = get_time();
	threads_init(philos, &env);
	wait_for_end(philos, &env);
	// pthread_mutex_unlock(&env.printing);
	threads_exit(philos, &env);
	return (0);
}