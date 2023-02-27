/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/02/27 14:44:50 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->printing);
	// if (!philo->env->stop_condition && !philo->env->max_ate)
	// 	printf("%s %s %s\n", timestamp, philo->pos_str, msg);
	printf("%lu %d %s\n", timestamp, philo->forks[0], msg);
	if (unlock)
		pthread_mutex_unlock(&philo->env->printing);
	// free(timestamp);
}

void	*func(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)param;
	env = philo->env;
	philo_print(" is thinking.", philo, 1);
	// printf("\nPhilosopher % d is thinking.", (int)philo->forks[0]);
	pthread_mutex_lock(&env->forks[philo->forks[0]]);
	pthread_mutex_lock(&env->forks[philo->forks[1]]);

	philo_print(" is eating.", philo, 1);
	// printf("\nPhilosopher % d is eating.", (int)philo->forks[0]);

	usleep(5000);
	pthread_mutex_unlock(&env->forks[philo->forks[0]]);
	pthread_mutex_unlock(&env->forks[philo->forks[1]]);
	philo_print(" Finished eating.", philo, 1);
	// printf("\nPhilosopher % d Finished eating ", (int)philo->forks[0]);
	
	return (NULL);
}

void	init_threads(t_philo *philos, t_env *env)
{
	int	i;
	
	philos = malloc(env->count * sizeof(*philos));
	env->forks = malloc(env->count * sizeof(*env->forks));
	env->start_time = get_time();
	if (!philos || !(env->forks))
			ft_return_error("🔴 Error in Alloc!\n");
	i = -1;
	while (++i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL))
			ft_return_error("🔴 Error in Mutex Init!\n");
	}
	i = -1;
	while (++i < env->count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, (void *)func, (void *)&philos[i]))
			ft_return_error("🔴 Error in Thread Create!\n");
		philos[i].forks[0] = i;
		philos[i].forks[1] = (i + 1) % env->count;
		philos[i].env = env;
	}
	i = -1;
	while (++i < env->count)
	{
		if (pthread_join(philos[i].thread_id, NULL))
			ft_return_error("🔴 Error in Thread Join!\n");
	}
	i = -1;
	while (++i < env->count)
	{
		if (pthread_mutex_destroy(&env->forks[i]))
			ft_return_error("🔴 Error in Mutex Destroy!\n");
	}
	free(philos);
	free(env->forks);
}
