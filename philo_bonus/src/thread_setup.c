/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/23 15:43:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	process_create(t_philo *philos, t_env *env)
{
	pid_t	pid;
	int		i;

	env->sem_forks = sem_open("/forks", O_CREAT, 0666, env->count);
	sem_unlink("/forks");
	i = -1;
	while (++i < env->count)
	{
		pid = fork();
		if (pid)
		{
			philos[i].pid = pid;
		}
		else
		{
			philos[i].id = i + 1;
			philos[i].env = env;
			philos[i].ate_count = 0;
			philos[i].last_ate = get_time();
			routine(&philos[i]);
			return (0);
		}
	}
	return (0);
}

int	process_exit(t_philo *philos, t_env *env)
{
	int		i;
		
	i = -1;
	while (++i < env->count)
	{
		sleep(5);
		kill(philos[i].pid, SIGTERM);
		sem_post(env->sem_forks);
		printf("%d\n", env->is_dead); // does not share the same env
		waitpid(philos[i].pid, NULL, 0);
	}
	sem_close(env->sem_forks);
	return (0);
}
