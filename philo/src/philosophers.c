/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/01 15:04:25 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// static int	check_death(t_philo *philos, t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	(void)philos;
// 	while (i < env->count)
// 	{
// 		printf("a");
// 		i++;
// 	}
// 	return (0);
// }

static int	parse_params(int argc, char *argv[], t_env *env)
{
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_count_max = ft_atoi(argv[5]);
	else
		env->eat_count_max = 0;
	if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo			philos;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!parse_params(argc, argv, &env))
		return (ft_return_error(ERR_PARAM));
	init_threads(&philos, &env);
	// check_death(&philos, &env);
	return (0);
}
