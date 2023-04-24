/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/24 12:40:02 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	kill_int(int server_pid, int n)
{
	int	bit;

printf("sending...");
	bit = 32;
	while (bit--)
	{
		if (n >> bit & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(400);
	}
}

int	routine_eat(t_env *env, int i)
{
	// int	i;

	sem_wait(env->sem_forks);
	if (env->is_dead)
		return (1);
	print_status("has taken a fork", env, i);
	sem_wait(env->sem_forks);
	if (env->is_dead)
		return (1);
	print_status("has taken a fork", env, i);
	print_status("is eating", env, i);
	// philo->last_ate = get_time();
	// philo->ate_count++;
	// if (philo->ate_count == env->max_eat_count)
		// kill(getppid(), SIGUSR1);
	//* SENDSIG i *//
	kill_int(getppid(), i);
	return (0);
}

void	routine(t_env *env, int i)
{
	// t_env	*env;
	int		first;

	first = 1;
	// env = philo->env;
	while (!env->is_dead && !env->is_satiated)
	{
		if (i % 2 == 1 && i < env->count && first)
			first = 0 ;
		else
		{
			print_status("is thinking", env, i);
			if (routine_eat(env, i))
				return ;
		}
		ft_msleep(env->time_to_eat, env);
		sem_post(env->sem_forks);
		sem_post(env->sem_forks);
		print_status("is sleeping", env, i);
		ft_msleep(env->time_to_sleep, env);
	}
}
