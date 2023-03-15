/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:41:17 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 15:31:49 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
		philos[i].ffork = (i) % env->count;
		philos[i].sfork = (i + 1) % env->count;
		philos[i].env = env;
		philos[i].ate_count = 0;
		philos[i].last_ate = get_time();
		if (i % 2 == 0 && i < env->count - 1)
			routine_eat(&philos[i], env);
		if (pthread_create(&philos[i].thread_id, NULL, (void *)routine,
				(void *)&philos[i]))
			ft_return_error("🔴 Error in Thread Create!\n");
	}
}

void	threads_exit(t_philo *philos, t_env *env)
{
	int	i;

	if (env->count == 1)
		pthread_detach(philos[0].thread_id);
	i = -1;
	while (++i < env->count)
	{
		if (env->count > 1)
			if (pthread_join(philos[i].thread_id, NULL))
				ft_return_error("🔴 Error in Thread Join!\n");
	}
	pthread_mutex_destroy(&env->printing);
	i = -1;
	while (++i < env->count)
	{
		pthread_mutex_unlock(&env->forks[i]);
		if (pthread_mutex_destroy(&env->forks[i]))
			ft_return_error("🔴 Error in Mutex Destroy!\n");
	}
}
