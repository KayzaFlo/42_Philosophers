/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:55:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/09 14:51:35 by fgeslin          ###   ########.fr       */
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

typedef struct	s_env
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

typedef struct	s_philo
{
	int				id;
	int				ate_count;
	uint64_t		last_ate;
	struct s_env	*env;
	pthread_t		thread_id;
}	t_philo;

// Utils Str
int			ft_atoi(const char *str);
int			ft_return_error(char *msg);

// Utils Time
uint64_t	get_time(void);
void		ft_msleep(uint64_t duration, t_env *env);

void		print_status(char *msg, t_philo *philo, int unlock);

void		threads_init(t_philo *philos, t_env *env);
void		threads_exit(t_philo *philos, t_env *env);

#endif
