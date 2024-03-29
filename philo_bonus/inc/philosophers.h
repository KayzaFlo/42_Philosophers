/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:55:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/24 12:13:55 by fgeslin          ###   ########.fr       */
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
# include <signal.h>

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
	sem_t			*sem_forks;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				ate_count;
	uint64_t		last_ate;
	struct s_env	*env;
	pid_t			pid;
}	t_philo;

// Utils Str
int			atoi_overflow(const char *str);
int			ft_return_error(char *msg);
int			ft_strlen(char *str);

// Utils Time
uint64_t	get_time(void);
void		ft_msleep(uint64_t duration, t_env *env);

// Utils Print
void		print_status(char *msg, t_env *env, int i);
int			print_error(char *msg, int i);

// Parsing
int			parse_params(int argc, char *argv[], t_env *env);

// Threads
int			process_create(t_philo *philos, t_env *env);
int			process_exit(t_philo *philos, t_env *env);
int			routine_eat(t_env *env, int i);
void		routine(t_env *env, int i);

#endif
