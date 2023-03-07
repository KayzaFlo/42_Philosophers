/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/07 16:45:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->printing);
	if (!philo->env->do_stop)
		printf("%lu %d %s\n", timestamp, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->env->printing);
}

void	routine(t_philo *philo)
{
	// t_philo	*philo;
	t_env	*env;

	// philo = (t_philo *)param;
	env = philo->env;
	while (!env->do_stop)
	{
		philo_print("is thinking", philo, 1);
		pthread_mutex_lock(&env->forks[philo->id - 1]);
		philo_print("has taken a fork", philo, 1);
		pthread_mutex_lock(&env->forks[philo->id % env->count]);
		philo_print("has taken a fork", philo, 1);
		philo_print("is eating", philo, 1);
		philo->last_ate = get_time();
		philo->ate_count++;
		ft_msleep(env->time_to_eat, env);
		philo_print("is sleeping", philo, 1);
		pthread_mutex_unlock(&env->forks[philo->id - 1]);
		pthread_mutex_unlock(&env->forks[philo->id % env->count]);
		ft_msleep(env->time_to_sleep, env);
	}
}

/*
 ** @brief		Init
 **
 **	Description Heyo
 **
 **	@param[in]	philos
 **	@param[in]	env
 **	@return		return value
 */
void	threads_init(t_philo *philos, t_env *env)
{
	int	i;
	
	env->start_time = get_time();
	i = -1;
	while (++i < env->count)
		if (pthread_mutex_init(&env->forks[i], NULL))
			ft_return_error("🔴 Error in Mutex Init!\n");
pthread_mutex_init(&env->printing, NULL);
	i = -1;
	while (++i < env->count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, (void *)routine,
				(void *)&philos[i]))
			ft_return_error("🔴 Error in Thread Create!\n");
		// philos[i].forks[0] = i;
		// philos[i].forks[1] = (i + 1) % env->count;
		philos[i].id = i + 1;
		philos[i].env = env;
		philos[i].ate_count = 0;
		philos[i].last_ate = get_time();
	}
}

void	threads_exit(t_philo *philos, t_env *env)
{
	int	i;

	i = -1;
	if (env->count == 1)
		pthread_detach(philos[0].thread_id);
	else
	while (++i < env->count)
		if (pthread_join(philos[i].thread_id, NULL))
		// if (pthread_detach(philos[i].thread_id))
			ft_return_error("🔴 Error in Thread Join!\n");
	i = -1;
	while (++i < env->count)
	{
		pthread_mutex_unlock(&env->forks[i]);
		if (pthread_mutex_destroy(&env->forks[i]))
			ft_return_error("🔴 Error in Mutex Destroy!\n");
	}
	pthread_mutex_destroy(&env->printing);
	free(philos);
	free(env->forks);
}
