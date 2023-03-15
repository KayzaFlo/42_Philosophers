/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 15:29:38 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	routine_eat(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(&env->forks[philo->ffork]);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&env->forks[philo->sfork]);
	print_status("has taken a fork", philo);
	print_status("is eating", philo);
	philo->last_ate = get_time();
	philo->ate_count++;
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
			print_status("is thinking", philo);
			routine_eat(philo, env);
		}
		ft_msleep(env->time_to_eat, env);
		pthread_mutex_unlock(&env->forks[philo->ffork]);
		pthread_mutex_unlock(&env->forks[philo->sfork]);
		print_status("is sleeping", philo);
		ft_msleep(env->time_to_sleep, env);
	}
}
