/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/21 11:33:52 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	threads_init(t_philo *philos, t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL))
			return (print_error("🔴 Error in Mutex Init!\n", 1));
	}
	if (pthread_mutex_init(&env->printing, NULL))
		return (print_error("🔴 Error in Mutex Init!\n", 1));
	i = -1;
	while (++i < env->count)
	{
		philos[i].id = i + 1;
		philos[i].env = env;
		philos[i].ate_count = 0;
		philos[i].last_ate = get_time();
		if (i % 2 == 0 && i < env->count - 1)
			routine_eat(&philos[i], env);
		if (pthread_create(&philos[i].thread_id, NULL, (void *)routine,
				(void *)&philos[i]))
			return (print_error("🔴 Error in Thread Create!\n", 1));
	}
	return (0);
}

int	threads_exit(t_philo *philos, t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->count)
	{
		pthread_mutex_unlock(&env->forks[i]);
		if (pthread_join(philos[i].thread_id, NULL))
			return (print_error("🔴 Error in Thread Join!\n", 1));
	}
	i = -1;
	while (++i < env->count)
	{
		pthread_mutex_unlock(&env->forks[i]);
		if (pthread_mutex_destroy(&env->forks[i]))
			return (print_error("🔴 Error in Mutex Destroy!\n", 1));
	}
	if (pthread_mutex_destroy(&env->printing))
		return (print_error("🔴 Error in Mutex Destroy!\n", 1));
	return (0);
}
