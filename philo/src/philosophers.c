/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 17:13:45 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	wait_for_end(t_philo *philos, t_env *env)
{
	int	i;
	int	satiated_count;

	satiated_count = 0;
	while (satiated_count != env->count)
	{
		i = -1;
		satiated_count = 0;
		while (++i < env->count && !env->is_dead)
		{
			if ((int)(get_time() - philos[i].last_ate) > env->time_to_die)
			{
				print_status("died", &philos[i]);
				env->is_dead = 1;
				return ;
			}
			if (env->max_eat_count && i < env->count)
				if (philos[i].ate_count >= env->max_eat_count)
					satiated_count++;
		}
	}
	pthread_mutex_lock(&env->printing);
	printf("Each philosopher ate at least %d time(s).\n", env->max_eat_count);
	env->is_satiated = 1;
	pthread_mutex_unlock(&env->printing);
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (print_error("🟡 Usage: " KWHT KBLD "./client " KNRM
				KUND "number_of_philosophers" KNRM " " KUND "time_to_die" KNRM
				" " KUND "time_to_eat" KNRM " " KUND "time_to_sleep" KNRM " "
				KUND "[nbr_of_times_each_philosopher_must_eat]" KNRM "\n", 0));
	if (!parse_params(argc, argv, &env))
		return (print_error("🟡 Usage: " KWHT "Incorrect parameters.\n", 0));
	philos = malloc(env.count * sizeof(*philos));
	env.forks = malloc(env.count * sizeof(*env.forks));
	if (!philos || !(env.forks))
		return (print_error("🔴 Error in Alloc!\n", 1));
	if (threads_init(philos, &env))
		return (1);
	wait_for_end(philos, &env);
	if (threads_exit(philos, &env))
		return (1);
	free(philos);
	free(env.forks);
	return (0);
}
