/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:55:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/01 14:07:49 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
# include <pthread.h>

# define ERR_USAGE KYEL "🟡 Usage: " KWHT KBLD "./client " KNRM KUND\
  "number_of_philosophers" KNRM " " KUND "time_to_die" KNRM " " KUND\
  "time_to_eat" KNRM " " KUND "time_to_sleep" KNRM " " KUND\
  "[number_of_times_each_philosopher_must_eat]" KNRM "\n"
# define ERR_PARAM KYEL "🟡 Usage: " KWHT "Incorrect parameters.\n"

typedef struct s_env
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	pthread_mutex_t	picking;
}	t_env;

typedef struct s_philo
{
	int				forks[2];
	int				eat_count;
	struct s_env	*env;
	pthread_t		thread_id;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_return_error(char *msg);

void	init_threads(t_philo *philos, t_env *env);

#endif
