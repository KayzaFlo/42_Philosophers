/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/10 16:40:09 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_status(char *msg, t_philo *philo, int unlock)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->env->printing);
	timestamp = get_time() - philo->env->start_time;
	if (!philo->env->is_dead && !philo->env->is_satiated)
		printf("%lu %d %s\n", timestamp, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->env->printing);
}

void	routine(t_philo *philo)
{
	t_env	*env;
	int		first;

	first = 1;
	env = philo->env;
	while (!env->is_dead && !env->is_satiated)
	{
		if (philo->id % 2 == 1 && philo->id < env->count && first)
			first = 0 ;
		else
		{
		print_status("is thinking", philo, 1);
		pthread_mutex_lock(&env->forks[philo->ffork]);
		print_status("has taken a fork", philo, 1);
		pthread_mutex_lock(&env->forks[philo->sfork]);
		print_status("has taken a fork", philo, 1);
		print_status("is eating", philo, 1);
		philo->last_ate = get_time();
		philo->ate_count++;
		}
		ft_msleep(env->time_to_eat, env);
		pthread_mutex_unlock(&env->forks[philo->ffork]);
		pthread_mutex_unlock(&env->forks[philo->sfork]);
		print_status("is sleeping", philo, 1);
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
	
	pthread_mutex_init(&env->printing, NULL);
	i = -1;
	while (++i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL))
			ft_return_error("🔴 Error in Mutex Init!\n");
	}
	i = -1;
	while (++i < env->count)
	{
		philos[i].id = i + 1;
		// philos[i].ffork = (i + i % 2) % env->count;
		// philos[i].sfork = (i + 1 - i % 2) % env->count;
		philos[i].ffork = (i) % env->count;
		philos[i].sfork = (i + 1) % env->count;
		philos[i].env = env;
		philos[i].ate_count = 0;
		philos[i].last_ate = get_time();

		if (i % 2 == 0 && i < env->count-1)
		{
			print_status("is thinking", &philos[i], 1);
			pthread_mutex_lock(&env->forks[philos[i].ffork]);
			print_status("has taken a fork", &philos[i], 1);
			pthread_mutex_lock(&env->forks[philos[i].sfork]);
			print_status("has taken a fork", &philos[i], 1);
			print_status("is eating", &philos[i], 1);
			philos[i].last_ate = get_time();
			philos[i].ate_count++;
		}

		if (pthread_create(&philos[i].thread_id, NULL, (void *)routine,
				(void *)&philos[i]))
			ft_return_error("🔴 Error in Thread Create!\n");
	}
}

void	threads_exit(t_philo *philos, t_env *env)
{
	int	i;

	pthread_mutex_destroy(&env->printing);
	if (env->count == 1)
		pthread_detach(philos[0].thread_id);
			// pthread_join(philos[0].thread_id, NULL);
	i = -1;
	while (++i < env->count)
	{
		if (env->count > 1)
			// if (pthread_detach(philos[i].thread_id))
			if (pthread_join(philos[i].thread_id, NULL))
				ft_return_error("🔴 Error in Thread Join!\n");
	}
	i = -1;
	while (++i < env->count)
	{
		pthread_mutex_unlock(&env->forks[i]);
		if (pthread_mutex_destroy(&env->forks[i]))
			ft_return_error("🔴 Error in Mutex Destroy!\n");
	}
}
