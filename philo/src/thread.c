/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/02 15:53:14 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->printing);
	// if (!philo->env->stop_condition && !philo->env->max_ate)
	// 	printf("%s %s %s\n", timestamp, philo->pos_str, msg);
	printf("%lu %d %s\n", timestamp, philo->forks[0] + 1, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->env->printing);
	// free(timestamp);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)param;
	env = philo->env;
	philo_print("is thinking", philo, 1);
	// pthread_mutex_lock(&env->picking); //
	pthread_mutex_lock(&env->forks[philo->forks[0]]);
	philo_print("has taken a fork", philo, 1);
	pthread_mutex_lock(&env->forks[philo->forks[1]]);
	philo_print("has taken a fork", philo, 1);
	// pthread_mutex_unlock(&env->picking); //
	philo->last_ate = get_time();
	philo_print("is eating", philo, 1);
	// usleep(env->time_to_eat * 1000);
	ft_msleep(env->time_to_eat, env);
	if (env->max_ate && ++philo->ate_count >= env->max_ate)
	{
		env->do_stop = 1;
		pthread_mutex_unlock(&env->forks[philo->forks[0]]);
		pthread_mutex_unlock(&env->forks[philo->forks[1]]);
		// return (NULL);
	}
	philo_print("is sleeping", philo, 1);
	pthread_mutex_unlock(&env->forks[philo->forks[0]]);
	pthread_mutex_unlock(&env->forks[philo->forks[1]]);
	// usleep(env->time_to_sleep * 1000);
	ft_msleep(env->time_to_sleep, env);
	if (!env->do_stop)
		routine(param);
	return (NULL);
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
pthread_mutex_init(&env->picking, NULL);
pthread_mutex_init(&env->printing, NULL);
	i = -1;
	while (++i < env->count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, (void *)routine, (void *)&philos[i]))
			ft_return_error("🔴 Error in Thread Create!\n");
		philos[i].forks[0] = i;
		philos[i].forks[1] = (i + 1) % env->count;
		philos[i].env = env;
		philos[i].last_ate = get_time();
	}
}

void	threads_exit(t_philo *philos, t_env *env)
{
	int	i;

	i = -1;
	// if (env->count == 1)
	// 	pthread_detach(philos[0].thread_id);
	// else
	while (++i < env->count)
		if (pthread_detach(philos[i].thread_id))
		// if (pthread_detach(philos[i].thread_id))
			ft_return_error("🔴 Error in Thread Join!\n");
	i = -1;
	while (++i < env->count)
		if (pthread_mutex_destroy(&env->forks[i]))
			ft_return_error("🔴 Error in Mutex Destroy!\n");
	pthread_mutex_destroy(&env->picking);
	pthread_mutex_destroy(&env->printing);
	free(philos);
	free(env->forks);
}
