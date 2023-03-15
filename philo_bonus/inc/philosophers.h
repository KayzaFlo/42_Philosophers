/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:55:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 16:18:29 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <pthread.h>
# include <semaphore.h>

typedef struct s_env
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	int				is_dead;
	int				is_satiated;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				ate_count;
	uint64_t		last_ate;
	struct s_env	*env;
	pthread_t		thread_id;
}	t_philo;

#endif
