/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/21 11:34:32 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	routine_eat(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(&env->forks[(philo->id - 1) % env->count]);
	if (env->is_dead)
		return (1);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&env->forks[philo->id % env->count]);
	if (env->is_dead)
		return (1);
	print_status("has taken a fork", philo);
	print_status("is eating", philo);
	philo->last_ate = get_time();
	philo->ate_count++;
	return (0);
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
			if (routine_eat(philo, env))
				return ;
		}
		ft_msleep(env->time_to_eat, env);
		pthread_mutex_unlock(&env->forks[(philo->id - 1) % env->count]);
		pthread_mutex_unlock(&env->forks[philo->id % env->count]);
		print_status("is sleeping", philo);
		ft_msleep(env->time_to_sleep, env);
	}
}
